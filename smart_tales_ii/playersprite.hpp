#pragma once
#include "animatedsprite.hpp"

#include <string>

class PlayerSprite : public AnimatedSprite
{
private:
	sf::Texture texture;

public:
	void Load(const std::string & animationFile);

	PlayerSprite();
};

