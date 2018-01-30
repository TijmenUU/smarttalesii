#include "player.hpp"

#include <stdexcept>

void Player::Load(const std::string & textureSrc)
{
	if(!texture.loadFromFile(textureSrc))
	{
		throw std::runtime_error("Failed to load player texture from " + textureSrc);
	}
	setTexture(texture, true);
}

Player::Player()
	: Sprite(),
	texture()
{
}
