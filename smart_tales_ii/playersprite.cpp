#include "playersprite.hpp"

#include <stdexcept>

void PlayerSprite::Load(const std::string & animationFile)
{
	AnimatedSprite::Load(animationFile, texture);
}

PlayerSprite::PlayerSprite()
	: AnimatedSprite(),
	texture()
{
}
