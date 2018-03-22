#pragma once
#include "background.hpp"
#include "currencydisplayer.hpp"
#include "difficulty.hpp"
#include "gamemode.hpp"
#include "baseobstacle.hpp"
#include "playersprite.hpp"
#include "playerinventory.hpp"
#include "playerscore.hpp"
#include "scorebubble.hpp"

#include <list>
#include <vector>
#include <memory>

class RunningMode : public Gamemode
{
private:
	ScrollingBackground background;

	std::list<sf::Texture> textureStorage;
	std::list<Animation::Sheet> spriteSheetStorage;
	std::vector<std::unique_ptr<Obstacle::Base>> obstacleFactory;
	Difficulty gameDifficulty;
	
	std::vector<std::unique_ptr<Obstacle::Base>> obstacles;
	size_t obstacleSpawnIndex = 0;
	sf::Text obstacleHintText;
	bool drawObstacleHint = false;
	const float spawnTimeout = 2.5f; // in seconds
	float currentTimeout = 0.f; // in seconds
	float scrollVelocity = 0.f; // pixels per second

	Player::Score score;
	std::unique_ptr<CurrencyDisplayer> currencyDisplay;
	std::vector<ScoreBubble> scoreBubbles;

	PlayerSprite player;
	const Player::Inventory playerInventory;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void SpawnObstacle();
	void SpawnScoreBubble(const sf::Vector2f & mousePos, const unsigned int score);
	
	void GameOver();
	void Reset();

	bool SurpressDraw() const override;
	bool SurpressUpdate() const override;
	void OnEnter() override;

	// May throw a runtime exception if it cannot load the required files and assets
	Animation::Sheet & LoadSheet(const std::string file);
	void Load() override;

	// if it returns true, game over
	bool UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input);
	void UpdateHints();
	void UpdateScoreBubbles(const sf::Time & elapsed);
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	RunningMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Inventory & inventory);
};
