#include "shopmode.hpp"

#include "gamemanager.hpp"
#include "runningmode.hpp"

void ShopMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(title, states);
}

void ShopMode::Load()
{
	manager.PopAllBelow(this);

	sf::Font * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in RunningMode.");
	}

	title.setFont(*fontPtr);
	title.setCharacterSize(36);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.f);
	title.setString("Shop");
}

void ShopMode::Update(const sf::Time & timeElapsed, const Inputhandler & input)
{
	// debug
	if(input.PointingDeviceReleasedEvent())
	{
		manager.PushGamemode(new RunningMode(fonts, manager, playerInventory));
		return;
	}
	// end debug
}

ShopMode::ShopMode(Fonts & fontsRef, GameManager & managerRef, const Player::Inventory & inventory)
	:Gamemode(fontsRef, managerRef),
	playerInventory(inventory),
	title()
{
}
