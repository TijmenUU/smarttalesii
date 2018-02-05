#include "runningmode.hpp"
#include "vectormath.hpp"

#include <iomanip> // debug
#include <iostream> // debug
#include <sstream> // debug

// Config files
const std::string cObstacleDefinitionFile = "obstacles.txt";
const std::string cGameDifficultyFile = "difficulty.txt";

// Textures
const std::string cPlayerTexture = "texture/player.png";
const std::string cBackgroundWallTexture = "texture/runningbackground.png";

// Utility consts
const float cWorldWidth = 1280.f; // in pixels
const float cWorldHeight = 720.f; // in pixels
const float cHintBorder = cWorldWidth * 0.75f; // in pixels, the minimum obstacle position for the hint to show up

void Runningmode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);

	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		if(obstacles[i].IsNeutralized())
			continue;
		target.draw(obstacles[i], states);
	}

	target.draw(player, states);

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

void Runningmode::Reset()
{
	background.Reset();

	obstacles.clear();

	obstacleSpawnIndex = 0;
	currentTimeout = 0.f;
	scrollVelocity = gameDifficulty.startVelocity;

	const float groundLevel = 0.66f * cWorldHeight;
	const auto playerBounds = player.getGlobalBounds();
	const sf::Vector2f playerPos(playerBounds.width, groundLevel - playerBounds.height);
	player.setPosition(playerPos);

	score.Reset();
}

void Runningmode::UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input)
{
	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0; --i)
	{
		auto & obstacle = obstacles[i];
		if(obstacle.Update(elapsed, -scrollVelocity, input))
		{
			score.AddNeutralization(VectorMathF::Distance(obstacle.GetPosition(), player.getPosition()));
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
		if(obstaclePosition.x <= cHintBorder)
		{
			obstacleHintText.setString(obstacles[0].GetNeutralizationHint());
			const auto textbounds = obstacleHintText.getGlobalBounds();
			const float xpos = obstacles[0].GetCenter().x - (textbounds.width / 2.f);
			obstacleHintText.setPosition(xpos, obstaclePosition.y - (textbounds.height + 10.f));

			drawObstacleHint = true;
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
	obstacleHintText.setCharacterSize(32);
	obstacleHintText.setFillColor(sf::Color::White);
	obstacleHintText.setOutlineColor(sf::Color::Black);
	obstacleHintText.setOutlineThickness(1.f);

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

	UpdateObstacles(timeElapsed, input);

	UpdateHints();

	const auto elapsedSeconds = timeElapsed.asSeconds();

	score.distance += elapsedSeconds * scrollVelocity;

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
	player(),
	score(),
	paused(false)
{

}
