#include "scoremode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "overlaymode.hpp"
#include "shopmode.hpp"

void ScoreMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(title, states);
	target.draw(gotoShopButton, states);
}

void ScoreMode::Load()
{
	manager.PopAllBelow(this);
	manager.PushGamemode(new OverlayMode(resourceCache, manager, false));

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in RunningMode.");
	}

	gotoShopButton.LoadFromFile("animation/navigationbutton_large.txt", navigationButtonTexture);
	gotoShopButton.SetPosition(sf::Vector2f(Alignment::GetCenterOffset(gotoShopButton.GetGlobalbounds().width, cWorldWidth / 2.f), cWorldHeight - 120.f));
	sf::Text buttonText("Go to shop", *fontPtr, 30U);
	buttonText.setFillColor(sf::Color::White);
	gotoShopButton.SetText(buttonText);

	title.setFont(*fontPtr);
	title.setCharacterSize(36);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.f);
	title.setString("Score Screen");
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 0.f);
}

void ScoreMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(gotoShopButton.Update(elapsed, input))
	{
		playerInventory.AddCurrency(playerScore.GetCurrency());
		manager.PushGamemode(new ShopMode(resourceCache, manager, playerInventory));
		return;
	}
}

ScoreMode::ScoreMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Score & score, const Player::Inventory & inventory)
	:	Gamemode(resourceCacheRef, managerRef),
	playerScore(score),
	playerInventory(inventory),
	navigationButtonTexture(),
	gotoShopButton(),
	title()
{
	playerInventory.AddCurrency(score.GetCurrency());
}
