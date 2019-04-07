#include "../resourcecache.hpp"
#include "background.hpp"
#include <cmath>
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

	wallSpriteWidth = wallTexture.getSize().x;
	const int repetitions = static_cast<int>(std::ceil(width / wallSpriteWidth)) + 2;

	wallSprite.setTexture(wallTexture);

	wallSprite.setTextureRect(sf::IntRect(0, 0, repetitions * wallSpriteWidth, wallTexture.getSize().y));

	Reset();
}
