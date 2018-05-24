#include "informationcard.hpp"

#include "resourcecache.hpp"

void InformationCard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(fadeTimeOut <= 0.f)
	{
		target.draw(image, states);
		target.draw(subtitle, states);
	}
}

void InformationCard::Update(const sf::Time & elapsed)
{
	if(fadeTimeOut > 0.f)
	{
		fadeTimeOut -= elapsed.asSeconds();
	}
	else
	{
		if(colorValue < 255)
		{
			colorValue += 4;
			if(colorValue > 255)
				colorValue = 255;

			const auto fillColor = sf::Color(255, 255, 255, static_cast<uint8_t>(colorValue));
			subtitle.setFillColor(fillColor);
			image.setColor(fillColor);

			subtitle.setOutlineColor(sf::Color(0, 0, 0, colorValue));		
		}
	}
}

void InformationCard::SetPosition(const float x, const float y)
{
	const float padding = 10.f;

	image.setPosition(x, y);
	const auto imgBounds = image.getLocalBounds();

	const auto textBounds = subtitle.getLocalBounds();
	subtitle.setPosition((imgBounds.width / 2 + x) - (textBounds.left + textBounds.width / 2),
		padding + y + imgBounds.height + textBounds.top);
}

InformationCard::InformationCard(const std::string & textureFile, const std::string & description, const float _fadeTimeOut)
	: fadeTimeOut(_fadeTimeOut),
	colorValue(0),
	image(ResourceCache::GetInstance().GetTexture(textureFile)),
	subtitle(description, ResourceCache::GetInstance().GetFont("commodore"), 22)
{
	image.setColor(sf::Color::Transparent);
	subtitle.setFillColor(sf::Color::Transparent);
	subtitle.setOutlineColor(sf::Color::Transparent);
	subtitle.setOutlineThickness(1.f);

	SetPosition(0.f, 0.f);
}
