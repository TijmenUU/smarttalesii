#include "runningmode.hpp"

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
}

void Runningmode::Load()
{
	obstacleDefinitions = Definition::GetObstacles(cObstacleDefinitionFile);
	gameDifficulty = Definition::GetDifficulty(cGameDifficultyFile);
	scrollVelocity = gameDifficulty.startVelocity;

	const sf::Vector2f basepos(1280.f, 0.f);
	for(size_t i = 0; i < obstacleDefinitions.size(); ++i)
	{
		spawnPositions.emplace_back(basepos.x + i * 400, 720.f / 2);
		obstacles.emplace_back(obstacleDefinitions[i], spawnPositions.back());
	}
}

void Runningmode::Update(const sf::Time & timeElapsed, const Inputhandler & input)
{
	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		auto & obstacle = obstacles[i];
		obstacle.Update(timeElapsed, -scrollVelocity, input);

		const auto size = obstacle.GetSize();
		const auto position = obstacle.GetPosition();
		if(position.x + size.x < 0.f)
		{
			obstacle.SetNeutralized(false);
			obstacle.SetPosition(spawnPositions[i]);
		}
	}

	scrollVelocity += gameDifficulty.incrementVelocity * timeElapsed.asSeconds();
	if(scrollVelocity > gameDifficulty.incrementMaxVelocity)
	{
		scrollVelocity = gameDifficulty.incrementMaxVelocity;
	}
}

Runningmode::Runningmode()
	: obstacleDefinitions(),
	spawnPositions(),
	obstacles(),
	gameDifficulty(),
	scrollVelocity(0.f)
{
}
