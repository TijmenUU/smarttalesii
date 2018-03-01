#pragma once
#include "button.hpp"

class TextButton : public Button
{
private:
	sf::Text buttonText;

protected:
	void UpdateTextPosition(const sf::Vector2f & position);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetPosition(const sf::Vector2f & position) override;

	virtual sf::Text & GetText();

	virtual void SetText(const sf::Text & text);
	virtual void SetString(const std::string & s);
	virtual void SetFont(sf::Font & font);

	TextButton(const bool enabled = true, const bool down = false);
};