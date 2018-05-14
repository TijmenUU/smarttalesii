#include "background.hpp"

#include "resourcecache.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

void ScrollingBackground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(wallSprite, states);
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

ScrollingBackground::ScrollingBackground(const float width)
{
	auto & cache = ResourceCache::GetInstance();
	auto & wallTexture = cache.GetMutableTexture("runningbackground");
	wallTexture.setRepeated(true);
	wallTexture.setSmooth(false);
#pragma warning(suppress: 4244) // The textures used are too small to overflow a float here
	wallSpriteWidth = wallTexture.getSize().x;
	const int repetitions = static_cast<int>(std::ceil(width / wallSpriteWidth)) + 2;

	wallSprite.setTexture(wallTexture);
#pragma warning(suppress: 4244) // Texture rect is pixel perfect, so the loss of precision from float to int is no problem
	wallSprite.setTextureRect(sf::IntRect(0, 0, repetitions * wallSpriteWidth, wallTexture.getSize().y));

	Reset();
}
