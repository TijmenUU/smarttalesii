#pragma once
#include "animatedsprite.hpp"

#include <string>

class Player : public AnimatedSprite
{
private:
	sf::Texture texture;

public:
	void Load(const std::string & animationFile);

	Player();
};

