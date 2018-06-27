#pragma once
#include "definitions.hpp"
#include "gesture.hpp"
#include "inputhandler.hpp"

#include <SFML/Graphics.hpp>

class Obstacle : public sf::Drawable
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	sf::Sprite sprite;
	sf::CircleShape debugShape; // debug
	uint8_t gestureNeutralizeFlag;
	SwipeGesture gesture;
	ObstacleType type;
	bool neutralized;

public:
	bool IsNeutralized() const;

	// in world coordinates, not screen size necessarily!
	sf::Vector2f GetSize() const;
	sf::Vector2f GetCenter() const;
	sf::Vector2f GetPosition() const;
	ObstacleType GetType() const;

	void SetNeutralized(const bool value);
	void SetPosition(const sf::Vector2f & position);

	bool CollidesWith(const sf::FloatRect & other) const;

	// Return value indicates neutralized status
	bool Update(const sf::Time & elapsed, const float velocity, const Inputhandler & input);

	Obstacle(const Definition::Obstacle & obstacleDefinition, const sf::Vector2f & spawnPosition);
};

