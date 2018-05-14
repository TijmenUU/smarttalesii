/*
	background.hpp

	This class simply scrolls the background by moving it back and
	forth. As soon as the background is more than a single sprite
	width over the edge, it moves a single sprite width back.
*/
#pragma once
#include <SFML/Graphics.hpp>

// TODO add random scrolling elements like paintings and clocks if time allows
class ScrollingBackground : public sf::Drawable
{
private:
	sf::Sprite wallSprite;
	float wallSpriteWidth = -1;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	void Reset();
	void Update(const sf::Time & elapsed, const float scrollVelocity);

	ScrollingBackground(const float width);
};