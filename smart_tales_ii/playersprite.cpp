#include "playersprite.hpp"

#include <stdexcept>

void PlayerSprite::Load(const std::string & animationFile)
{
	AnimatedSprite::LoadFromFile(animationFile, texture);
}

PlayerSprite::PlayerSprite()
	: AnimatedSprite(),
	texture()
{
}
