#include "../../util/alignmenthelp.hpp"
#include "textbutton.hpp"

void TextButton::UpdateTextPosition()
{
	const auto center = Util::GetRectangleCenter(buttonSprite.getGlobalBounds());
	const auto offset = Util::GetRectangleCenter(buttonText.getLocalBounds());
	// We can use the offset alone because we're passing in global bounds, so it is already in world space
	
	buttonText.setPosition(center - offset);
}

void TextButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(buttonText, states);
}

void TextButton::SetPosition(const sf::Vector2f & position)
{
	Button::SetPosition(position);
	UpdateTextPosition();
}

sf::Text & TextButton::GetText()
{
	return buttonText;
}

void TextButton::SetText(const sf::Text & text)
{
	buttonText = text;
	UpdateTextPosition();
}

void TextButton::SetString(const std::string & s)
{
	buttonText.setString(s);
	UpdateTextPosition();
}

void TextButton::SetFont(sf::Font & font)
{
	buttonText.setFont(font);
	UpdateTextPosition();
}

TextButton::TextButton(const Animation::Sheet & buttonSheet,
	const bool enabled, 
	const bool down)
	: Button(buttonSheet, enabled, down)
{
}
