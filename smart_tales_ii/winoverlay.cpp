#include "winoverlay.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"

void WinOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(title, states);

	target.draw(first, states);
	target.draw(second, states);
	target.draw(third, states);

	target.draw(body, states);
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
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 75.f);

	//body.setFont(font);
	//body.setCharacterSize(32);
	//body.setFillColor(sf::Color::Transparent);
	//body.setOutlineColor(sf::Color::Transparent);
	//body.setOutlineThickness(2.f);
	//body.setString("Victory is the child of\npreparation and determination.\n\n-Sean Hampton");
	//body.setPosition(Alignment::GetCenterOffset(body.getGlobalBounds().width, cWorldWidth / 2.f), 250.f);
	const float infoCardYPos = 175;
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
			body.setFillColor(fillColor);

			const sf::Color outlineColor(0, 0, 0, colorValue);
			title.setOutlineColor(outlineColor);
			body.setOutlineColor(outlineColor);

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
