#include "runningmode.hpp"

#include <sstream>

const std::string cObstacleDefinitionFile = "obstacles.txt";
const std::string cGameDifficultyFile = "difficulty.txt";

void Runningmode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		if(obstacles[i].IsNeutralized())
			continue;
		target.draw(obstacles[i], states);
	}
	
	target.draw(debugTxt, states); // debug
}

void Runningmode::Reset()
{
	obstacles.clear();

	obstacleSpawnIndex = 0;
	currentTimeout = 0.f;
	scrollVelocity = gameDifficulty.startVelocity;
	distanceCovered = 0.0;
}

void Runningmode::Load()
{
	obstacleDefinitions = Definition::GetObstacles(cObstacleDefinitionFile);
	gameDifficulty = Definition::GetDifficulty(cGameDifficultyFile);
	Reset();
}

void Runningmode::Update(const sf::Time & timeElapsed, const Inputhandler & input)
{
	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0 ; --i)
	{
		auto & obstacle = obstacles[i];
		obstacle.Update(timeElapsed, -scrollVelocity, input);

		const auto size = obstacle.GetSize();
		const auto position = obstacle.GetPosition();
		if(position.x + size.x < 0.f)
		{
			if(!obstacle.IsNeutralized())
			{
				Reset(); 
			}
			else
			{
				obstacles.erase(obstacles.begin() + i);
			}
		}
		else if(obstacle.IsNeutralized())
		{
			obstacles.erase(obstacles.begin() + i);
		}
	}

	const auto elapsedSeconds = timeElapsed.asSeconds();

	distanceCovered += elapsedSeconds * scrollVelocity;

	// debug
	std::stringstream ss;
	ss << "Current scroll velocity " << scrollVelocity << " pixels per second.\n";
	ss << "Distance of " << distanceCovered << " pixels covered.";
	debugTxt.setString(ss.str());
	// end debug

	scrollVelocity += gameDifficulty.incrementVelocity * elapsedSeconds;
	if(scrollVelocity > gameDifficulty.incrementMaxVelocity)
	{
		scrollVelocity = gameDifficulty.incrementMaxVelocity;
	}

	currentTimeout += elapsedSeconds;
	if(obstacles.size() == 0 || (currentTimeout > spawnTimeout && obstacles.back().GetPosition().x < (1280.f - 400.f)))
	{
		currentTimeout = 0.f;
		if(obstacleSpawnIndex >= obstacleDefinitions.size())
		{
			obstacleSpawnIndex = 0;
		}
		obstacles.emplace_back(obstacleDefinitions[obstacleSpawnIndex], sf::Vector2f(1280.f, 360.f));
		++obstacleSpawnIndex;
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
	distanceCovered(0.0),
	debugTxt("", *fontPtr)// debug
{
	// debug
	debugTxt.setFillColor(sf::Color::White);
	debugTxt.setOutlineColor(sf::Color::Black);
	debugTxt.setOutlineThickness(1.f);
	debugTxt.setPosition(0.f, 0.f);
	// end debug
}
