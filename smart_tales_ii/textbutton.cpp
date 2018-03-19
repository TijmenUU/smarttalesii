#include "textbutton.hpp"

#include "alignmenthelp.hpp"

void TextButton::UpdateTextPosition(const sf::Vector2f & position)
{
	const auto center = Alignment::GetRectangleCenter(buttonSprite.getGlobalBounds());
	const auto offset = Alignment::GetCenterOffset(buttonText.getLocalBounds(), center);
	// We can use the offset alone because we're passing in global bounds, so it is already in world space
	
	buttonText.setPosition(offset);
}

void TextButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(buttonText, states);
}

void TextButton::SetPosition(const sf::Vector2f & position)
{
	Button::SetPosition(position);
	UpdateTextPosition(position);
}

sf::Text & TextButton::GetText()
{
	return buttonText;
}

void TextButton::SetText(const sf::Text & text)
{
	buttonText = text;
	UpdateTextPosition(buttonSprite.getPosition());
}

void TextButton::SetString(const std::string & s)
{
	buttonText.setString(s);
	UpdateTextPosition(buttonSprite.getPosition());
}

void TextButton::SetFont(sf::Font & font)
{
	buttonText.setFont(font);
	UpdateTextPosition(buttonSprite.getPosition());
}

TextButton::TextButton(const Animation::Sheet & buttonSheet,
	bool enabled, 
	const bool down)
	: Button(buttonSheet, enabled, down),
	buttonText()
{
}
