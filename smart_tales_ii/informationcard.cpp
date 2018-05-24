#include "informationcard.hpp"

#include "resourcecache.hpp"

void InformationCard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(image, states);
	target.draw(subtitle, states);
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

InformationCard::InformationCard(const std::string & textureFile, const std::string & description)
	: image(ResourceCache::GetInstance().GetTexture(textureFile)),
	subtitle(description, ResourceCache::GetInstance().GetFont("commodore"), 22)
{
	subtitle.setFillColor(sf::Color::White);
	subtitle.setOutlineColor(sf::Color::Black);
	subtitle.setOutlineThickness(1.f);

	SetPosition(0.f, 0.f);
}
