#pragma once
#include "animatedsprite.hpp"
#include "gesture.hpp"
#include "inputhandler.hpp"
#include "obstacledefinition.hpp"


class Obstacle : public AnimatedSprite
{
private:
	// TODO Do something more sensible than a raw pointer
	const ObstacleDefinition * definitionPtr;
	SwipeGesture gesture;
	bool neutralized;

public:
	bool IsNeutralized() const;

	ObstacleType GetType() const;
	const std::string & GetNeutralizationHint() const;
	sf::Vector2f GetNeutralizationHintPosition() const;

	// Return value indicates neutralized status
	bool Update(const sf::Time & elapsed, const float velocity, const Inputhandler & input);

	Obstacle(const ObstacleDefinition * definition);
};

