#pragma once
#include <SFML\Graphics.hpp>

class GameoverMessage : public sf::Drawable
{
private:
	sf::Text catchPhrase;
	sf::Text information;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	GameoverMessage(const float centerX, const float y);
};