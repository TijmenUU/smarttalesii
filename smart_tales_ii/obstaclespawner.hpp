#pragma once
#include "playerinventory.hpp"

// obstacle definitions
#include "furnitureobstacle.hpp"
#include "doorobstacle.hpp"
#include "lightobstacle.hpp"
#include "phoneobstacle.hpp"

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

	void Load(const Player::Inventory & inventory, const float floorYposition);

	void Update(const sf::Time elapsed, std::vector<std::unique_ptr<Obstacle::Base>> & toInsertIn);
};

