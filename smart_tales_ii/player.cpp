#include "player.hpp"

#include <stdexcept>

void Player::Load(const std::string & animationFile)
{
	AnimatedSprite::Load(animationFile, texture);
}

Player::Player()
	: AnimatedSprite(),
	texture()
{
}
