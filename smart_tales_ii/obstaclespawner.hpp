/*
	obstaclespawner.hpp

	A helper class that inserts the next "random" object on
	a given interval. The order is seeded and uses a uniform
	distribution.
*/

#pragma once
#include "baseobstacle.hpp"
#include "playerinventory.hpp"

#include <memory>
#include <random>
#include <vector>

class ObstacleSpawner
{
private:
	std::vector<std::unique_ptr<Obstacle::Base>> obstacleFactory;
	const float spawnTimeout = 2.5f; // in seconds
	float currentSpawnTimeout = 0.f; // in seconds
	
	// mutable member variables
	mutable std::default_random_engine randomEngine = std::default_random_engine(8274);
	mutable std::uniform_int_distribution<unsigned int> dist;

	void InsertObstacle(std::vector<std::unique_ptr<Obstacle::Base>> & v) const;

public:
	void Reset();

	void Load(const Player::Inventory & inventory, const float spawnXposition, const float floorYposition);

	void Update(const sf::Time elapsed, std::vector<std::unique_ptr<Obstacle::Base>> & toInsertIn, const float worldRightBorderX);
};

