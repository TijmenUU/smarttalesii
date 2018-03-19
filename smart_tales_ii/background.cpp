#include "background.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

void ScrollingBackground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(wallSprite, states);
}

void ScrollingBackground::Load(const std::string & textureFile)
{
	if(!wallTexture.loadFromFile(textureFile))
	{
		throw std::runtime_error("Cannot load texture file " + textureFile);
	}
	wallTexture.setRepeated(true);
	wallTexture.setSmooth(false);

	wallSpriteWidth = wallTexture.getSize().x;
	const int repetitions = static_cast<int>(std::ceil(worldWidth / wallSpriteWidth)) + 2;

	wallSprite.setTexture(wallTexture);
	wallSprite.setTextureRect(sf::IntRect(0, 0, repetitions * wallSpriteWidth, wallTexture.getSize().y));

	Reset();
}

void ScrollingBackground::Reset()
{
	wallSprite.setPosition(0.f, 0.f);
}

void ScrollingBackground::Update(const sf::Time & elapsed, const float scrollVelocity)
{
	auto position = wallSprite.getPosition();
	position.x += elapsed.asSeconds() * scrollVelocity;

	if(position.x < (-wallSpriteWidth))
	{
		position.x += wallSpriteWidth;
	}

	wallSprite.setPosition(position);
}

ScrollingBackground::ScrollingBackground(const float _worldWidth)
	: wallSprite(),
	wallTexture(),
	wallSpriteWidth(-1.f),
	scrollPosition(0.f, 0.f),
	worldWidth(_worldWidth)
{
}
