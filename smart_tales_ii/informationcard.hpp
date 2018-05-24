/*
	informationcard.hpp

	Simple helper class used in winoverlay.hpp / .cpp.

	Counts down its timeout and after that it starts fading
	in the subtitle and image.
*/

#pragma once
#include <SFML/Graphics.hpp>

class InformationCard : public sf::Drawable
{
private:
	float fadeTimeOut;
	int colorValue;
	sf::Sprite image;
	sf::Text subtitle;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Update(const sf::Time & elapsed);

	void SetPosition(const float x, const float y);

	InformationCard(const std::string & textureFile, const std::string & description, const float _fadeTimeOut);
};