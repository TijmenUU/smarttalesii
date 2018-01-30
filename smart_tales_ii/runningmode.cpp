#include "runningmode.hpp"
#include "vectormath.hpp"

#include <iomanip> // debug
#include <iostream> // debug
#include <sstream> // debug

const std::string cObstacleDefinitionFile = "obstacles.txt";
const std::string cGameDifficultyFile = "difficulty.txt";
const std::string cPlayerTexture = "textures/player.png";

const float cWorldWidth = 1280.f;
const float cWorldHeight = 720.f;

void Runningmode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
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
	obstacleDefinitions = Definition::GetObstacles(cObstacleDefinitionFile);
	gameDifficulty = Definition::GetDifficulty(cGameDifficultyFile);
	player.Load(cPlayerTexture);
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

Runningmode::Runningmode(sf::Font * font)
	: fontPtr(font),
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
	debugTxt("", *fontPtr, 22)// debug
{
	// debug
	debugTxt.setFillColor(sf::Color::Black);
	debugTxt.setPosition(0.f, 0.f);
	// end debug
}
