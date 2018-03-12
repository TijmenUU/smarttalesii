#pragma once
#include <SFML\Graphics.hpp>

// TODO add random scrolling elements like paintings and clocks if time allows
class ScrollingBackground : public sf::Drawable
{
private:
	sf::Texture wallTexture;
	sf::Sprite wallSprite;
	float wallSpriteWidth;
	sf::Vector2f scrollPosition;
	const float worldWidth;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	// May throw an std::runtime_error if texturefile cannot be loaded
	void Load(const std::string & textureStorage);
	void Reset();
	void Update(const sf::Time & elapsed, const float scrollVelocity);

	ScrollingBackground(const float _worldWidth);
};