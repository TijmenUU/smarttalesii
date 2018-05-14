/*
	runningmode.hpp

	A large class representing the main game.
	It has a few debug options:
		- keyboard key K to kill yourself
		- keyboard key W to instantly win
		- keyboard key - to slow down the scrolling velocity
		- keyboard key + to speed up the scrolling velocity

	It surpresses the update of underlying gamemodes
	It surpresses the drawing of underlying gamemodes
*/

#pragma once
#include "background.hpp"
#include "currencydisplayer.hpp"
#include "difficulty.hpp"
#include "gamemode.hpp"
#include "obstaclespawner.hpp"
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

	Difficulty gameDifficulty;
	
	std::vector<std::unique_ptr<Obstacle::Base>> obstacles;
	ObstacleSpawner obstacleSpawner;
	sf::Text obstacleHintText;
	bool drawObstacleHint = false;
	
	// We have to use a secondary running time keeping variable so that the game pause
	// works correctly, instead of using a more obvious sf::Clock object.
	unsigned int runningtimeMs = 0U;
	float scrollVelocity = 0.f; // pixels per second

	Player::Score score;
	CurrencyDisplayer currencyDisplay;
	std::vector<ScoreBubble> scoreBubbles;

	PlayerSprite player;
	const Player::Inventory playerInventory;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void GameOver(const Obstacle::Type cause);
	void Reset();

	bool SurpressDraw() const override;
	bool SurpressUpdate() const override;
	void OnEnter() override;

	// May throw a runtime exception if it cannot load the required files and assets
	void Setup() override;

	// if it returns true, game over
	bool UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input);
	void UpdateHints();
	void UpdateScoreBubbles(const sf::Time & elapsed);
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	RunningMode(const Player::Inventory & inventory);
};
