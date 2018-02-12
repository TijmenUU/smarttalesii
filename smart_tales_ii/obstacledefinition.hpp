#pragma once
#include "animatedsprite.hpp"

#include <SFML\Graphics.hpp>

enum class ObstacleType
{
	Unknown = -1,
	Furniture,
	Door,
	Light,
	Phone
};

class ObstacleDefinition
{
public:
	ObstacleType type;
	sf::Texture texture;
	AnimatedSprite animatedSprite;

	sf::Vector2f interactionLocalPos, neutralizationHintLocalPos;
	float interactionRadius;
	float minimalDistance;
	uint8_t neutralizationSwipes;
	std::string neutralizationHint;

	void LoadFromFile(const std::string & filename);

	ObstacleDefinition();
};