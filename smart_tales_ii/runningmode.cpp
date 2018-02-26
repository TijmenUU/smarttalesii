#include "runningmode.hpp"
#include "gamemanager.hpp"
#include "pausemode.hpp"
#include "vectormath.hpp"

#include <array>
#include <iomanip>
#include <iostream> // debug
#include <memory>
#include <sstream>

// Config files
const std::array<std::string, 4> cObstacleDefinitionFiles =
{
	"obstacle/door.txt",
	"obstacle/furniture.txt",
	"obstacle/light.txt",
	"obstacle/phone.txt"
};
const std::string cGameDifficultyFile = "difficulty.txt";

// Resources
const std::string cPlayerAnimationFile = "animation/player.txt";
const std::string cBackgroundWallTexture = "texture/runningbackground.png";

// Utility consts
const float cFloorY = 520.f; // in pixels
const std::string cScoreString = "SCORE ";

void RunningMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);

	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		target.draw(obstacles[i], states);
	}

	for(size_t i = 0; i < scoreBubbles.size(); ++i)
	{
		target.draw(scoreBubbles[i], states);
	}

	target.draw(player, states);

	target.draw(scoreText, states);

	if(drawObstacleHint)
		target.draw(obstacleHintText, states);
}

void RunningMode::SpawnObstacle()
{
	if(obstacleSpawnIndex >= obstacleDefinitions.size())
	{
		obstacleSpawnIndex = 0;
	}

	obstacles.emplace_back(obstacleDefinitions[obstacleSpawnIndex].get());
	
	auto & newObstacle = obstacles.back();
	newObstacle.SetAnimation("active");
	newObstacle.setPosition(cWorldWidth, cFloorY - newObstacle.getGlobalBounds().height);
	
	++obstacleSpawnIndex;
}

void RunningMode::SpawnScoreBubble(const Obstacle & obstacle, const float score, const float bonusScore)
{
	auto * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		std::cerr << "Error loading font commodore for score bubble.\n";
		return;
	}

	scoreBubbles.emplace_back(*fontPtr, obstacle.GetNeutralizationHintPosition(), score, bonusScore);
}

void RunningMode::GameOver()
{
	// TODO start gamemode switch here to score screen
	manager.PushGamemode(new PauseMode(fonts, manager, "Game over! Press P to retry"));

	Reset();
	return;
}

void RunningMode::Reset()
{
	background.Reset();

	obstacles.clear();

	obstacleSpawnIndex = 0;
	currentTimeout = 0.f;
	scrollVelocity = gameDifficulty.GetStartScrollVelocity();

	score.Reset();
	scoreBubbles.clear();
}

bool RunningMode::SurpressDraw() const
{
	return true;
}

bool RunningMode::SurpressUpdate() const
{
	return true;
}

void RunningMode::UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input)
{
	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0; --i)
	{
		auto & obstacle = obstacles[i];
		if(obstacle.IsNeutralized())
		{
			obstacle.Update(elapsed, -scrollVelocity, input);
			if(obstacle.IsAnimationFinished() || (obstacle.getPosition().x + obstacle.getGlobalBounds().width) < 0.f)
			{
				obstacles.erase(obstacles.begin() + i);
				continue; // make sure we cannot use the deleted obj anymore
			}
		}
		else
		{
			if(obstacle.Update(elapsed, -scrollVelocity, input))
			{
				const auto obstacleCenter = obstacle.GetCenter();
				const float playerObstacleDist = VectorMathF::Distance(obstacleCenter, player.getPosition());

				const auto neutralizationScore = score.CalculateNeutralizationScore(1); // could be made a constexpr
				const auto bonusScore = score.CalculateBonusScore(playerObstacleDist);
				score.AddBonusScore(bonusScore);
				score.AddNeutralization();

				SpawnScoreBubble(obstacle, neutralizationScore, bonusScore);
			}
			else if(obstacle.getGlobalBounds().intersects((player.getGlobalBounds())))
			{
				// debug
				std::cout << "Run over! Final score: " << score.GetTotalScore();
				std::cout << " with " << score.distance << " covered and a scroll velocity of " << scrollVelocity << '\n';
				// end debug
				GameOver();
				return;
			}
		}
	}
}

void RunningMode::UpdateHints()
{
	drawObstacleHint = false;
	if(obstacles.size() > 0U)
	{
		for(size_t i = 0; i < obstacles.size(); ++i)
		{
			const auto & obstacle = obstacles[i];
			if(!obstacle.IsNeutralized())
			{
				auto obstaclePosition = obstacle.getPosition();
				if(obstaclePosition.x <= gameDifficulty.GetHintBorderXCoord())
				{
					obstacleHintText.setString(obstacle.GetNeutralizationHint());
					auto position = obstacle.GetNeutralizationHintPosition();
					position.x -= obstacleHintText.getGlobalBounds().width / 2.f;
					obstacleHintText.setPosition(position);

					drawObstacleHint = true;
					break;
				}
			}
		}
	}
}

void RunningMode::UpdateScoreDisplay()
{
	// Content
	std::stringstream ss;
	ss << cScoreString;
	ss << std::setfill('0') << std::setw(6);
	ss << static_cast<int>(score.GetTotalScore());
	scoreText.setString(ss.str());
	
	// Positioning
	const float width = scoreText.getGlobalBounds().width;
	const auto oldPosition = scoreText.getPosition();
	scoreText.setPosition((cWorldWidth / 2) - (width / 2), oldPosition.y);
}

void RunningMode::UpdateScoreBubbles(const sf::Time & elapsed)
{
	for(int64_t i = static_cast<int64_t>(scoreBubbles.size()) - 1; i >= 0; --i)
	{
		if(scoreBubbles[i].Update(elapsed))
		{
			scoreBubbles.erase(scoreBubbles.begin() + i);
		}
	}
}

void RunningMode::Load()
{
	background.Load(cBackgroundWallTexture);
	for(size_t i = 0; i < cObstacleDefinitionFiles.size(); ++i)
	{
		obstacleDefinitions.emplace_back(new ObstacleDefinition());
		obstacleDefinitions.back()->LoadFromFile(cObstacleDefinitionFiles[i]);
		obstacleDefinitions.back()->animatedSprite.SetAnimation("active");
	}
	gameDifficulty.LoadFromFile(cGameDifficultyFile);//GetDifficulty(cGameDifficultyFile);
	
	player.Load(cPlayerAnimationFile);
	player.SetAnimation("run");
	const auto playerBounds = player.getGlobalBounds();
	player.setPosition(playerBounds.width, cFloorY - playerBounds.height);

	sf::Font * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in RunningMode.");
	}
	//const_cast<sf::Texture&>(fontPtr->getTexture(32)).setSmooth(false);
	obstacleHintText.setFont(*fontPtr);
	obstacleHintText.setCharacterSize(26);
	obstacleHintText.setFillColor(sf::Color::White);
	obstacleHintText.setOutlineColor(sf::Color::Black);
	obstacleHintText.setOutlineThickness(2.f);

	scoreText.setFont(*fontPtr);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(2.f);
	scoreText.setPosition(0.f, 15.f);
}

void RunningMode::Update(const sf::Time & timeElapsed, const Inputhandler & input)
{
	if(input.WasKeyReleased(sf::Keyboard::Key::P))
	{
		manager.PushGamemode(new PauseMode(fonts, manager));
		return;
	}

	background.Update(timeElapsed, -scrollVelocity);

	UpdateScoreBubbles(timeElapsed);

	UpdateObstacles(timeElapsed, input);

	player.Update(timeElapsed);

	UpdateHints();

	const auto elapsedSeconds = timeElapsed.asSeconds();

	score.distance += elapsedSeconds * scrollVelocity;

	UpdateScoreDisplay();

	// Anything affected by the scrolling velocity should be updated BEFORE this line
	scrollVelocity += gameDifficulty.GetScrollIncrementVelocity() * elapsedSeconds;
	if(scrollVelocity > gameDifficulty.GetMaxScrollVelocity())
	{
		scrollVelocity = gameDifficulty.GetMaxScrollVelocity();
	}

	currentTimeout += elapsedSeconds;
	if(obstacles.size() == 0 || (currentTimeout > spawnTimeout && obstacles.back().getPosition().x < (cWorldWidth - 400.f)))
	{
		currentTimeout = 0.f;
		SpawnObstacle();
	}
}

void RunningMode::OnExit()
{
	// Update the last achieved score?
}

void RunningMode::OnEnter()
{
	Reset();
}

RunningMode::RunningMode(Fonts & fontsRef, GameManager & managerRef, const Player::Inventory & inventory)
	: Gamemode(fontsRef, managerRef),
	background(cWorldWidth),
	obstacleDefinitions(),
	obstacles(),
	gameDifficulty(),
	obstacleSpawnIndex(0),
	obstacleHintText(),
	drawObstacleHint(false),
	spawnTimeout(2.f),
	currentTimeout(spawnTimeout),
	scrollVelocity(0.f),
	score(),
	scoreText(),
	scoreBubbles(),
	player(),
	playerInventory(inventory)
{

}
