#include "scoremode.hpp"

#include "gamemanager.hpp"
#include "shopmode.hpp"

void ScoreMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(title, states);
}

void ScoreMode::Load()
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
	title.setString("Score Screen");
}

void ScoreMode::Update(const sf::Time & timeElapsed, const Inputhandler & input)
{
	// debug
	if(input.PointingDeviceReleasedEvent())
	{
		manager.PushGamemode(new ShopMode(fonts, manager, playerInventory));
		return;
	}
	// end debug
}

ScoreMode::ScoreMode(Fonts & fontsRef, GameManager & managerRef, const Player::Score & score, const Player::Inventory & inventory)
	:	Gamemode(fontsRef, managerRef),
	playerScore(score),
	playerInventory(inventory),
	title()
{
	playerInventory.AddCurrency(score.GetCurrency());
}
