#pragma once
#include "gamemode.hpp"
#include "obstacles.hpp"

#include <vector>

class Runningmode : public Gamemode
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	std::vector<Definition::Obstacle> obstacleDefinitions;
	std::vector<sf::Vector2f> spawnPositions;
	std::vector<Obstacle> obstacles;
	Definition::Difficulty gameDifficulty;
	float scrollVelocity; // pixels per second

public:
	// May throw a runtime exception if it cannot load the required files and assets
	void Load() override;
	void Update(const sf::Time & timeElapsed, const Inputhandler & input) override;

	Runningmode();
};

