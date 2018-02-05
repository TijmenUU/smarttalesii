#pragma once
#include "background.hpp"
#include "gamemode.hpp"
#include "obstacles.hpp"
#include "player.hpp"
#include "score.hpp"

#include <vector>

class Runningmode : public Gamemode
{
private:
	ScrollingBackground background;

	std::vector<Definition::Obstacle> obstacleDefinitions;
	Definition::Difficulty gameDifficulty;
	
	std::vector<Obstacle> obstacles;
	size_t obstacleSpawnIndex;
	sf::Text obstacleHintText;
	bool drawObstacleHint;
	const float spawnTimeout; // in seconds
	float currentTimeout; // in seconds
	float scrollVelocity; // pixels per second

	Player player;
	Score score;
	bool paused;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void SpawnObstacle();
	void Reset();

	void UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input);
	void UpdateHints();

public:
	// May throw a runtime exception if it cannot load the required files and assets
	void Load() override;
	void Update(const sf::Time & timeElapsed, const Inputhandler & input) override;

	Runningmode(Fonts & fontsRef);
};

