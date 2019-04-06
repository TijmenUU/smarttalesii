/*
	textbutton.hpp

	A button with text centered in it.
*/

#pragma once
#include "button.hpp"
#include <SFML/Graphics/Text.hpp>

class TextButton : public Button
{
protected:
	sf::Text buttonText;

	void UpdateTextPosition();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetPosition(const sf::Vector2f & position) override;

	virtual sf::Text & GetText();

	virtual void SetText(const sf::Text & text);
	virtual void SetString(const std::string & s);
	virtual void SetFont(sf::Font & font);

	TextButton(const Animation::Sheet & buttonSheet,
		const bool enabled = true, 
		const bool down = false);
};