#pragma once
#include "background.hpp"
#include "difficulty.hpp"
#include "gamemode.hpp"
#include "obstacles.hpp"
#include "player.hpp"
#include "score.hpp"
#include "scorebubble.hpp"

#include <vector>

class RunningMode : public Gamemode
{
private:
	ScrollingBackground background;

	std::vector<std::unique_ptr<ObstacleDefinition>> obstacleDefinitions;
	Difficulty gameDifficulty;
	
	std::vector<Obstacle> obstacles;
	size_t obstacleSpawnIndex;
	sf::Text obstacleHintText;
	bool drawObstacleHint;
	const float spawnTimeout; // in seconds
	float currentTimeout; // in seconds
	float scrollVelocity; // pixels per second

	Score score;
	sf::Text scoreText;
	std::vector<ScoreBubble> scoreBubbles;

	Player player;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void SpawnObstacle();
	void SpawnScoreBubble(const Obstacle & obstacle, const float score, const float bonusScore);
	
	void GameOver();
	void Reset();

	bool SurpressDraw() const override;
	bool SurpressUpdate() const override;
	void OnExit() override;
	void OnEnter() override;

	// May throw a runtime exception if it cannot load the required files and assets
	void Load() override;

	void UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input);
	void UpdateHints();
	void UpdateScoreDisplay();
	void UpdateScoreBubbles(const sf::Time & elapsed);
	void Update(const sf::Time & timeElapsed, const Inputhandler & input) override;

public:
	RunningMode(Fonts & fontsRef, GameManager & managerRef);
};

