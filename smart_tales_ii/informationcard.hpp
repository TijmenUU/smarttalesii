#pragma once
#include <SFML/Graphics.hpp>

class InformationCard : public sf::Drawable
{
private:
	sf::Sprite image;
	sf::Text subtitle;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetFillColor(const sf::Color & c);
	void SetOutlineColor(const sf::Color & c);

	void SetPosition(const float x, const float y);

	InformationCard(const std::string & textureFile, const std::string & description);
};