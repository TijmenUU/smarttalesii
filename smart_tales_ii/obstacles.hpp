#pragma once
#include "animatedsprite.hpp"
#include "gesture.hpp"
#include "inputhandler.hpp"
#include "obstacledefinition.hpp"

class Obstacle : public sf::Drawable
{
private:
	const ObstacleDefinition * definitionPtr;
	AnimatedSprite obstacleSprite, sensorSprite;
	SwipeGesture gesture;
	bool neutralized;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Neutralize();
	bool IsNeutralized() const;
	bool IsObstacleAnimationFinished() const;
	sf::FloatRect GetObstacleGlobalBounds() const;

	ObstacleType GetType() const;
	const std::string & GetNeutralizationHint() const;
	sf::Vector2f GetNeutralizationHintPosition() const;
	sf::Vector2f GetObstacleCenter() const;
	sf::Vector2f GetObstaclePosition() const;

	void SetPosition(const sf::Vector2f & p);

	// Return value indicates neutralized status
	bool Update(const sf::Time & elapsed, 
		const float velocity, 
		const Inputhandler & input,
		const sf::FloatRect & playerBounds);

	Obstacle(const ObstacleDefinition * definition);
};

