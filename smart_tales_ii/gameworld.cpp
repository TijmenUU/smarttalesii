#include "gameworld.hpp"

#include <cmath>
#include <ctime>

void GameWorld::Update(const sf::Time & timeElapsed,
	const Inputhandler & input,
	const sf::View & view)
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

void GameWorld::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		if(obstacles[i].IsNeutralized())
			continue;
		target.draw(obstacles[i], states);
	}
}

GameWorld::GameWorld(sf::Font * fontPointer,
	const unsigned int windowWidth,
	const unsigned int windowHeight)
: fontPtr(fontPointer),
mode(0),
obstacleDefinitions(Definition::GetObstacles(cObstacleDefinitionFile)),
spawnPositions(),
obstacles(),
gameDifficulty(Definition::GetDifficulty(cGameDifficultyFile)),
scrollVelocity(gameDifficulty.startVelocity)
{
	const sf::Vector2f basepos(windowWidth, 0.f);
	for(size_t i = 0; i < obstacleDefinitions.size(); ++i)
	{
		spawnPositions.emplace_back(basepos.x + i * 400, windowHeight / 2);
		obstacles.emplace_back(obstacleDefinitions[i], spawnPositions.back());
	}
}
