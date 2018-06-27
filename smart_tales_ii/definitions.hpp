#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <vector>

enum class SwipeType : uint8_t
{
	None = 0,
	InProgress = 1,
	Tap = 2,
	Vertical_Upwards = 4,
	Vertical_Downwards = 8,
	Horizontal_LeftToRight = 16,
	Horizontal_RightToLeft = 32,
};

enum class ObstacleType : uint8_t
{
	None = 0,
	Furniture = 1,
	Door,
	Lightswitch,
	Phone
};

namespace Definition
{
	struct Obstacle
	{
		ObstacleType type;
		std::string textureSourceFile;
		sf::Texture texture;

		float interactionRadius;
		float minimalDistance;
		uint8_t neutralizationSwipes;

		Obstacle(const std::string & definitionline);
	};

	// May throw an std::runtime_error when file is not accessible
	std::vector<Obstacle> GetObstacles(const std::string & definitionFile);

	struct Difficulty
	{
		float startVelocity;
		float incrementInterval;
		float incrementVelocity;
		float incrementMaxVelocity;
	};

	Difficulty GetDifficulty(const std::string & definitionFile);
}


