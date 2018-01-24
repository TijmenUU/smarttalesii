#pragma once
#include "inputhandler.hpp"
#include "obstacles.hpp"

#include <string>
#include <vector>

const std::string cObstacleDefinitionFile = "obstacles.txt";
const std::string cGameDifficultyFile = "difficulty.txt";

class GameWorld : public sf::Drawable
{
private:
	// sf::Drawable override
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
protected:
	sf::Font * fontPtr;
	int mode;
	
	// These vars should be moved into a gamemode class soon
	std::vector<Definition::Obstacle> obstacleDefinitions;
	std::vector<sf::Vector2f> spawnPositions;
	std::vector<Obstacle> obstacles;
	Definition::Difficulty gameDifficulty;
	float scrollVelocity; // pixels per second

public:
	void Update(const sf::Time & timeElapsed,
		const Inputhandler & input,
		const sf::View & view);

	GameWorld(sf::Font * fontPointer,
		const unsigned int windowWidth,
		const unsigned int windowHeight);
};
