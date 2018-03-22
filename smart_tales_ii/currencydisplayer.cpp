#include "currencydisplayer.hpp"

#include "alignmenthelp.hpp"
#include "resourcecache.hpp"

#include <iomanip>
#include <sstream>
#include <string>

void CurrencyDisplayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(coin, states);
	target.draw(text, states);
}

void CurrencyDisplayer::UpdateText()
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(5);
	ss << currentValue;

	text.setString(ss.str());
}

void CurrencyDisplayer::CenterOn(const float x, const float y)
{
	const auto coinBounds = coin.getLocalBounds();
	const auto textBounds = text.getLocalBounds();
	const float hor_padding = 10.f;

	const auto textYOffset = (textBounds.height / 2.f) + textBounds.top;
	const auto textXOffset = (textBounds.width / 2.f) + textBounds.left;
	text.setPosition(x - textXOffset, y - textYOffset);

	const float coinYOffset = coinBounds.height / 2.f;
	coin.setPosition(x + textXOffset + hor_padding, y - coinYOffset);
}

void CurrencyDisplayer::SetValue(const unsigned int v, const bool animate)
{
	if(animate)
	{
		targetValue = v;
	}
	else
	{
		targetValue = v;
		currentValue = v;
	}

	UpdateText();
}

void CurrencyDisplayer::Update(const sf::Time & elapsed)
{
	if(currentValue != targetValue)
	{
		if(currentValue < targetValue)
		{
			++currentValue;
		}
		else
		{
			--currentValue;
		}
		UpdateText();
	}
}

CurrencyDisplayer::CurrencyDisplayer()
	: coin(ResourceCache::GetInstance().GetTexture("coin")),
	text("00000", ResourceCache::GetInstance().GetFont("commodore"), 32)
{
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.f);
}
