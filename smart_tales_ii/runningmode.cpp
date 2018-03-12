#include "runningmode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "scoremode.hpp"
#include "vectormath.hpp"
#include "winoverlay.hpp"

// Obstacles
#include "furnitureobstacle.hpp"
#include "doorobstacle.hpp"
#include "lightobstacle.hpp"
#include "phoneobstacle.hpp"

#include <array>
#include <iomanip>
#include <iostream> // debug
#include <memory>
#include <sstream>

// Config files
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
		target.draw(*(obstacles[i]), states);
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
	currentTimeout = 0;

	if(obstacleSpawnIndex >= obstacleFactory.size())
	{
		obstacleSpawnIndex = 0;
	}

	auto * copy = obstacleFactory[obstacleSpawnIndex]->Clone();
	obstacles.emplace_back(copy);
	
	++obstacleSpawnIndex;
}

void RunningMode::SpawnScoreBubble(const Obstacle::Base & obstacle, const unsigned int score)
{
	auto * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		std::cerr << "Error loading font commodore for score bubble.\n";
		return;
	}

	scoreBubbles.emplace_back(*fontPtr, obstacle.GetScoreBubbleSpawnPosition(), score);
}

void RunningMode::GameOver()
{
	manager.Pop(); // delete our created overlay
	manager.PushGamemode(new ScoreMode(resourceCache, manager, score, playerInventory));
	return;
}

void RunningMode::Reset()
{
	background.Reset();

	obstacles.clear();

	obstacleSpawnIndex = 0;
	currentTimeout = 0.f;
	// TODO tweak this initial scroll velocity expression
	scrollVelocity = gameDifficulty.GetStartScrollVelocity() + playerInventory.GetSensorUpgradeCount() * 25.f;

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

bool RunningMode::UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input)
{
	const auto playerBounds = player.getGlobalBounds();
	const float displacement = elapsed.asSeconds() * -scrollVelocity;

	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0; --i)
	{
		auto & obstacle = *(obstacles[i]);

		if(obstacle.CanDespawn())
		{
			obstacles.erase(obstacles.begin() + i);
			continue; // make sure we cannot use the deleted obj anymore
		}

		const auto wasNeutralized = obstacle.IsNeutralizedByPlayer();
		obstacle.Update(elapsed, input, displacement, playerBounds);
		
		if(wasNeutralized != obstacle.IsNeutralizedByPlayer())
		{
			const auto obstacleCenter = obstacle.GetNeutralizationPosition();
			const float playerObstacleDist = VectorMathF::Distance(obstacleCenter, player.getPosition());
			
			const auto currencyScore = score.GetNeutralizationCurrency(playerObstacleDist);
			SpawnScoreBubble(obstacle, currencyScore);
		}
		else if(!obstacle.IsUnharmful() && obstacle.GetKillBounds().intersects(playerBounds))
		{
			// debug
			std::cout << "Run over! Currency earned this run: " << score.GetTotalCurrency();
			std::cout << " with a distance of " << score.distance;
			std::cout << " covered and a scroll velocity of " << scrollVelocity << '\n';
			std::cout << "\tKilled by a <" << Obstacle::GetString(obstacle.GetType()) << ">\n";
			// end debug
			GameOver();
			return true;
		}
	}

	return false;
}

void RunningMode::UpdateHints()
{
	drawObstacleHint = false;
	if(obstacles.size() > 0U)
	{
		for(size_t i = 0; i < obstacles.size(); ++i)
		{
			const auto & obstacle = *(obstacles[i]);
			if(!obstacle.IsUnharmful())
			{
				auto obstaclePosition = obstacle.GetNeutralizationPosition();
				if(obstaclePosition.x <= gameDifficulty.GetHintBorderXCoord())
				{
					obstacleHintText.setString(Obstacle::GetHintString(obstacle.GetType()));
					const auto hintPosition = obstacle.GetHintPosition();
					obstacleHintText.setPosition(Alignment::GetCenterOffset(obstacleHintText.getLocalBounds(), hintPosition));

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
	ss << static_cast<int>(score.GetTotalCurrency());
	scoreText.setString(ss.str());
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
	manager.PopAllBelow(this);

	background.Load(cBackgroundWallTexture);
	
	obstacleFactory.emplace_back(new Obstacle::Furniture(playerInventory.HasObstacleCounter(Obstacle::Type::Furniture)));
	obstacleFactory.emplace_back(new Obstacle::Door(playerInventory.HasObstacleCounter(Obstacle::Type::Door)));
	obstacleFactory.emplace_back(new Obstacle::Light(playerInventory.HasObstacleCounter(Obstacle::Type::Light)));
	obstacleFactory.emplace_back(new Obstacle::Phone(playerInventory.HasObstacleCounter(Obstacle::Type::Phone)));
	for(size_t i = 0; i < obstacleFactory.size(); ++i)
	{
		obstacleFactory[i]->Load(obstacleTextureStorage);
		obstacleFactory[i]->SetPosition(sf::Vector2f(0.f, 0.f));
		obstacleFactory[i]->SetSpawnPosition(cWorldWidth, cFloorY);
	}

	gameDifficulty.LoadFromFile(cGameDifficultyFile);//GetDifficulty(cGameDifficultyFile);
	
	player.Load(cPlayerAnimationFile);
	player.SetAnimation("run"); // TODO set different animation depending on upgrades
	const auto playerBounds = player.getGlobalBounds();
	player.setPosition(playerBounds.width, cFloorY - playerBounds.height);

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in RunningMode.");
	}

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
	scoreText.setString(cScoreString + "000000");
	scoreText.setPosition(Alignment::GetCenterOffset(scoreText.getGlobalBounds().width, cWorldWidth / 2.f), 15.f);

	if(playerInventory.GetSensorUpgradeCount() > 3)
	{
		manager.PushGamemode(new WinOverlay(resourceCache, manager));
	}
	else
	{
		manager.PushGamemode(new UIOverlay(resourceCache, manager));
	}
}

void RunningMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	// debug
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		GameOver();
		return;
	}
	// end debug
	background.Update(elapsed, -scrollVelocity);

	UpdateScoreBubbles(elapsed);

	if(UpdateObstacles(elapsed, input))
		return;

	player.Update(elapsed);

	UpdateHints();

	const auto elapsedSeconds = elapsed.asSeconds();

	score.distance += elapsedSeconds * scrollVelocity;

	UpdateScoreDisplay();

	// Anything affected by the scrolling velocity should be updated BEFORE this line
	scrollVelocity += gameDifficulty.GetScrollIncrementVelocity() * elapsedSeconds;
	if(scrollVelocity > gameDifficulty.GetMaxScrollVelocity())
	{
		scrollVelocity = gameDifficulty.GetMaxScrollVelocity();
	}

	// TODO add better spawn algorithm
	currentTimeout += elapsedSeconds;
	if(obstacles.size() == 0)
	{
		SpawnObstacle();
	}
	else
	{
		const auto obstacleBounds = obstacles.back()->GetKillBounds();
		if(currentTimeout > spawnTimeout && obstacleBounds.width + obstacleBounds.left < cWorldWidth)
		{
			SpawnObstacle();
		}
	}
}

void RunningMode::OnEnter()
{
	Reset();
}

RunningMode::RunningMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Inventory & inventory)
	: Gamemode(resourceCacheRef, managerRef),
	background(cWorldWidth),
	obstacleTextureStorage(),
	obstacleFactory(),
	gameDifficulty(),
	obstacles(),
	obstacleSpawnIndex(0),
	obstacleHintText(),
	drawObstacleHint(false),
	spawnTimeout(2.5f),
	currentTimeout(0.f),
	scrollVelocity(0.f),
	score(),
	scoreText(),
	scoreBubbles(),
	player(),
	playerInventory(inventory)
{

}
