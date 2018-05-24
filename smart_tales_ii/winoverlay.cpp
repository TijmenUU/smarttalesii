#include "winoverlay.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"

void WinOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(idleTimeOut > 0.f)
	{
		return;
	}
	target.draw(background, states);
	target.draw(title, states);

	target.draw(first, states);
	target.draw(second, states);
	target.draw(third, states);
}

void WinOverlay::Setup()
{
	sf::Font & font = ResourceCache::GetInstance().GetFont("commodore");

	title.setFont(font);
	title.setCharacterSize(42);
	title.setFillColor(sf::Color::Transparent);
	title.setOutlineColor(sf::Color::Transparent);
	title.setOutlineThickness(2.f);
	title.setString("When life is a game, don't make it\n      too hard on yourself!");
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 100.f);

	const float infoCardYPos = 200;
	first.SetPosition(20, infoCardYPos);
	second.SetPosition(440, infoCardYPos);
	third.SetPosition(860, infoCardYPos);

	background.setPosition(0, 0);
	background.setSize(sf::Vector2f(cWorldWidth, cWorldHeight));
	background.setFillColor(sf::Color::Transparent);

	GameManager::GetInstance().PushGamemode(new UIOverlay(false));
}

void WinOverlay::Update(const sf::Time & elapsed, const Inputhandler & input)
{	
	if(idleTimeOut > 0.f)
	{
		idleTimeOut -= elapsed.asSeconds();
	}
	else
	{
		if(colorValue != 255)
		{
			colorValue += fadeIncrement;

			const sf::Color fillColor(255, 255, 255, colorValue);
			title.setFillColor(fillColor);

			first.SetFillColor(fillColor);
			second.SetFillColor(fillColor);
			third.SetFillColor(fillColor);

			const sf::Color outlineColor(0, 0, 0, colorValue);
			title.setOutlineColor(outlineColor);

			first.SetOutlineColor(outlineColor);
			second.SetOutlineColor(outlineColor);
			third.SetOutlineColor(outlineColor);

			background.setFillColor(sf::Color(0, 0, 0, colorValue / 2));
		}
	}
}

void WinOverlay::Show()
{
	idleTimeOut = 0.f;
}

WinOverlay::WinOverlay(const float timeOut)
	: idleTimeOut(timeOut),
	first("motionsensorlightbulb", "From simple motion\ntriggered lightbulbs..."),
	second("tovertafel", "...to game tables\nby Active Cues..."),
	third("sensara", "...to a complete sensor\nsuite by Sensara")
{
}
