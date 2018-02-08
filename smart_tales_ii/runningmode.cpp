#include "runningmode.hpp"
#include "vectormath.hpp"

#include <iomanip>
#include <iostream> // debug
#include <sstream>

// Config files
const std::string cObstacleDefinitionFile = "obstacles.txt";
const std::string cGameDifficultyFile = "difficulty.txt";

// Textures
const std::string cPlayerTexture = "texture/player.png";
const std::string cBackgroundWallTexture = "texture/runningbackground.png";

// Utility consts
const float cWorldWidth = 1280.f; // in pixels
const float cWorldHeight = 720.f; // in pixels
const std::string cScoreString = "SCORE ";

void Runningmode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);

	for(size_t i = 0; i < scoreBubbles.size(); ++i)
	{
		target.draw(scoreBubbles[i], states);
	}

	target.draw(player, states);

	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		if(obstacles[i].IsNeutralized())
			continue;
		target.draw(obstacles[i], states);
	}

	target.draw(scoreText, states);

	if(drawObstacleHint)
		target.draw(obstacleHintText, states);
}

void Runningmode::SpawnObstacle()
{
	if(obstacleSpawnIndex >= obstacleDefinitions.size())
	{
		obstacleSpawnIndex = 0;
	}

	const float groundlevel = (0.66f * cWorldHeight) - obstacleDefinitions[obstacleSpawnIndex].texture.getSize().y;
	obstacles.emplace_back(obstacleDefinitions[obstacleSpawnIndex], sf::Vector2f(cWorldWidth, groundlevel));
	++obstacleSpawnIndex;
}

void Runningmode::SpawnScoreBubble(const sf::Vector2f & obstaclePosition, const float score, const float bonusScore)
{
	auto * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		std::cerr << "Error loading font commodore for score bubble.\n";
		return;
	}

	scoreBubbles.emplace_back(*fontPtr, obstaclePosition, score, bonusScore);
}

void Runningmode::Reset()
{
	background.Reset();

	obstacles.clear();

	obstacleSpawnIndex = 0;
	currentTimeout = 0.f;
	scrollVelocity = gameDifficulty.startVelocity;

	score.Reset();
	scoreBubbles.clear();

	const float groundLevel = 0.66f * cWorldHeight;
	const auto playerBounds = player.getGlobalBounds();
	const sf::Vector2f playerPos(playerBounds.width, groundLevel - playerBounds.height);
	player.setPosition(playerPos);
}

void Runningmode::UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input)
{
	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0; --i)
	{
		auto & obstacle = obstacles[i];
		if(obstacle.Update(elapsed, -scrollVelocity, input))
		{
			const auto obstaclePosition = obstacle.GetPosition();
			const float playerObstacleDist = VectorMathF::Distance(obstaclePosition, player.getPosition());

			SpawnScoreBubble(obstaclePosition, score.CalculateNeutralizationScore(1), score.CalculateBonusScore(playerObstacleDist));

			score.AddNeutralization(playerObstacleDist);
			obstacles.erase(obstacles.begin() + i);
			continue;
		}

		if(obstacle.CollidesWith(player.getGlobalBounds()))
		{
			// debug
			std::cout << "Run over! Final score: " << score.GetTotalScore();
			std::cout << " with " << score.distance << " covered and a scroll velocity of " << scrollVelocity << '\n';
			// end debug
			Reset();
		}
	}
}

void Runningmode::UpdateHints()
{
	drawObstacleHint = false;
	if(obstacles.size() > 0U)
	{
		auto obstaclePosition = obstacles[0].GetPosition();
		if(obstaclePosition.x <= gameDifficulty.hintBorderX)
		{
			obstacleHintText.setString(obstacles[0].GetNeutralizationHint());
			const auto textbounds = obstacleHintText.getGlobalBounds();
			const float xpos = obstacles[0].GetCenter().x - (textbounds.width / 2.f);
			obstacleHintText.setPosition(xpos, obstaclePosition.y - (textbounds.height + 10.f));

			drawObstacleHint = true;
		}
	}
}

void Runningmode::UpdateScoreDisplay()
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

void Runningmode::UpdateScoreBubbles(const sf::Time & elapsed)
{
	for(int64_t i = static_cast<int64_t>(scoreBubbles.size()) - 1; i >= 0; --i)
	{
		if(scoreBubbles[i].Update(elapsed))
		{
			scoreBubbles.erase(scoreBubbles.begin() + i);
		}
	}
}

void Runningmode::Load()
{
	background.Load(cBackgroundWallTexture);
	obstacleDefinitions = Definition::GetObstacles(cObstacleDefinitionFile);
	gameDifficulty = Definition::GetDifficulty(cGameDifficultyFile);
	player.Load(cPlayerTexture);

	sf::Font * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in Runningmode.");
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
	scoreText.setPosition(0.f, 0.f);

	Reset();
}

void Runningmode::Update(const sf::Time & timeElapsed, const Inputhandler & input)
{
	if(input.WasKeyReleased(sf::Keyboard::Key::P))
	{
		paused = !paused;
	}

	/* Anything affected by pause should be after this statement */
	if(paused)
	{
		return;
	}

	background.Update(timeElapsed, -scrollVelocity);

	UpdateScoreBubbles(timeElapsed);

	UpdateObstacles(timeElapsed, input);

	UpdateHints();

	const auto elapsedSeconds = timeElapsed.asSeconds();

	score.distance += elapsedSeconds * scrollVelocity;

	UpdateScoreDisplay();

	// Anything affected by the scrolling velocity should be updated BEFORE this line
	scrollVelocity += gameDifficulty.incrementVelocity * elapsedSeconds;
	if(scrollVelocity > gameDifficulty.incrementMaxVelocity)
	{
		scrollVelocity = gameDifficulty.incrementMaxVelocity;
	}

	currentTimeout += elapsedSeconds;
	if(obstacles.size() == 0 || (currentTimeout > spawnTimeout && obstacles.back().GetPosition().x < (cWorldWidth - 400.f)))
	{
		currentTimeout = 0.f;
		SpawnObstacle();
	}
}

Runningmode::Runningmode(Fonts & fontsRef)
	: Gamemode(fontsRef),
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
	paused(false)
{

}
