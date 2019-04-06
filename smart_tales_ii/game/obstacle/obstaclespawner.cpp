#include "obstacles.hpp"
#include "obstaclespawner.hpp"

void ObstacleSpawner::InsertObstacle(std::vector<std::unique_ptr<Obstacle::Base>>& v) const
{
	const auto index = dist(randomEngine);
	auto * copy = obstacleFactory[index]->Clone();
	v.emplace_back(copy);
}

void ObstacleSpawner::Reset()
{
	currentSpawnTimeout = 0.f;
}

void ObstacleSpawner::Load(const Player::Inventory & inventory, const float spawnXposition, const float floorYposition)
{
	obstacleFactory.emplace_back(new Obstacle::Furniture(inventory.HasObstacleCounter(Obstacle::Type::Furniture)));
	obstacleFactory.emplace_back(new Obstacle::Door(inventory.HasObstacleCounter(Obstacle::Type::Door)));
	obstacleFactory.emplace_back(new Obstacle::Light(inventory.HasObstacleCounter(Obstacle::Type::Light)));
	obstacleFactory.emplace_back(new Obstacle::Phone(inventory.HasObstacleCounter(Obstacle::Type::Phone)));

	for(size_t i = 0; i < obstacleFactory.size(); ++i)
	{
		obstacleFactory[i]->SetPosition(sf::Vector2f(0.f, 0.f));
		obstacleFactory[i]->SetSpawnPosition(spawnXposition, floorYposition);
	}

	// set our normal distribution to the obstacleFactory range
	dist.param(std::uniform_int_distribution<unsigned int>::param_type(0, obstacleFactory.size() - 1));
}

void ObstacleSpawner::Update(const sf::Time elapsed, std::vector<std::unique_ptr<Obstacle::Base>>& toInsertIn, const float worldRightBorderX)
{
	currentSpawnTimeout += elapsed.asSeconds();
	if(currentSpawnTimeout > spawnTimeout)
	{
		if(toInsertIn.size() == 0)
		{
			currentSpawnTimeout = 0.f;
			InsertObstacle(toInsertIn);
			return;
		}

		const auto & lastObstacleSpawned = toInsertIn.back();
		const auto bounds = lastObstacleSpawned->GetKillBounds();
		// Make sure this obstacle is fully on screen
		// before we spawn the next obstacle in!
		if(bounds.left + bounds.width < worldRightBorderX)
		{
			currentSpawnTimeout = 0.f;
			InsertObstacle(toInsertIn);
			return;
		}
	}
}
