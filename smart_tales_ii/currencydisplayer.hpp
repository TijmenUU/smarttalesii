#pragma once
#include <SFML/Graphics.hpp>

class CurrencyDisplayer : public sf::Drawable
{
private:
	sf::Sprite coin;
	sf::Text text;

	unsigned int targetValue = 0U;
	unsigned int currentValue = 0U;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void UpdateText();

public:
	void CenterOn(const float x, const float y);
	void SetValue(const unsigned int v, const bool animate = true);

	void Update(const sf::Time & elapsed);

	CurrencyDisplayer(const sf::Texture & coinTexture, sf::Font & font);
};
