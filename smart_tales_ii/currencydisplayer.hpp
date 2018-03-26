#pragma once
#include <SFML/Graphics.hpp>

class CurrencyDisplayer : public sf::Drawable
{
private:
	sf::Sprite coin;
	sf::Text text;
	std::string label;
	
	const bool animatesFast;
	unsigned int decimalPlaces;
	unsigned int targetValue;
	unsigned int currentValue;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void UpdateText();

public:
	bool IsDoneAnimating() const;

	void CenterOn(const float x, const float y);
	void CenterOn(const sf::Vector2f & v);
	void SetValue(const unsigned int v, const bool animate = true);

	void Update(const sf::Time & elapsed);

	CurrencyDisplayer(const unsigned int numberCharCount = 5U, 
		const std::string && leadingLabel = "", 
		const unsigned int initialValue = 0U,
		const bool fastAnimation = true);
};
