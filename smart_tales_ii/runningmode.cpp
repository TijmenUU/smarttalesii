#include "runningmode.hpp"
#include "vectormath.hpp"

#include <iomanip> // debug
#include <iostream> // debug
#include <sstream> // debug

// Config files
const std::string cObstacleDefinitionFile = "obstacles.txt";
const std::string cGameDifficultyFile = "difficulty.txt";

// Textures
const std::string cPlayerTexture = "textures/player.png";
const std::string cBackgroundWallTexture = "textures/runningbackground.png";

// Utility consts
const float cWorldWidth = 1280.f; // in pixels
const float cWorldHeight = 720.f; // in pixels
const float cHintBorder = cWorldWidth / 3.f; // in pixels, the minimum position for the hint to show up

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
	
	target.draw(debugTxt, states); // debug
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

void Runningmode::Load()
{
	background.Load(cBackgroundWallTexture);
	obstacleDefinitions = Definition::GetObstacles(cObstacleDefinitionFile);
	gameDifficulty = Definition::GetDifficulty(cGameDifficultyFile);
	player.Load(cPlayerTexture);

	// debug
	sf::Font * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in Runningmode.");
	}
	debugTxt.setFont(*fontPtr);
	debugTxt.setCharacterSize(16);
	debugTxt.setFillColor(sf::Color::Black);
	debugTxt.setPosition(0.f, 0.f);
	// end debug

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
		debugTxt.setString("Game is paused."); // debug
		return;
	}

	background.Update(timeElapsed, -scrollVelocity);

	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0 ; --i)
	{
		auto & obstacle = obstacles[i];
		if(obstacle.Update(timeElapsed, -scrollVelocity, input))
		{
			score.AddNeutralization(VectorMathF::Distance(obstacle.GetPosition(), player.getPosition()));
			obstacles.erase(obstacles.begin() + i);
			continue;
		}

		if(obstacle.CollidesWith(player.getGlobalBounds()))
		{
			std::cout << "Run over! Final score: " << score.GetTotalScore();
			std::cout << " with " << score.distance << " covered and a scroll velocity of " << scrollVelocity << '\n';// debug
			Reset();
		}
	}

	const auto elapsedSeconds = timeElapsed.asSeconds();

	score.distance += elapsedSeconds * scrollVelocity;

	// debug
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1);
	ss << "Current scroll velocity " << scrollVelocity << " pixels per second.\n";
	ss << "Distance of " << score.distance << " pixels covered.\n";
	ss << "Score of " << score.GetTotalScore() << " achieved.";
	debugTxt.setString(ss.str());
	// end debug

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
	spawnTimeout(2.f),
	currentTimeout(spawnTimeout),
	scrollVelocity(0.f),
	player(),
	score(),
	paused(false),
	debugTxt()// debug
{

}
