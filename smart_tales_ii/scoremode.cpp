#include "scoremode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "shopmode.hpp"

void ScoreMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(title, states);
	target.draw(currencyEarned, states);
	target.draw(newBalance, states);
	target.draw(gotoShopButton, states);
}

bool ScoreMode::SurpressUpdate() const
{
	return true;
}

void ScoreMode::Load()
{
	//manager.PopAllBelow(this);
	manager.PushGamemode(new UIOverlay(resourceCache, manager, false));

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in ScoreMode.");
	}

	background.LoadFromFile("animation/scorebackground.txt", backgroundTexture);
	backgroundTexture.setSmooth(false);
	background.setPosition(0.f, 0.f);
	background.setScale(4.f, 4.f);
	background.SetAnimation("zoom");

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

	currencyEarned.setFont(*fontPtr);
	currencyEarned.setCharacterSize(24);
	currencyEarned.setFillColor(sf::Color::White);
	currencyEarned.setOutlineColor(sf::Color::Black);
	currencyEarned.setOutlineThickness(1.f);
	currencyEarned.setString("Currency earned: " + std::to_string(playerScore.GetTotalCurrency()));
	currencyEarned.setPosition(Alignment::GetCenterOffset(currencyEarned.getGlobalBounds().width, cWorldWidth / 2.f), 200.f);

	newBalance.setFont(*fontPtr);
	newBalance.setCharacterSize(24);
	newBalance.setFillColor(sf::Color::White);
	newBalance.setOutlineColor(sf::Color::Black);
	newBalance.setOutlineThickness(1.f);
	newBalance.setString("Your new balance: " + std::to_string(playerScore.GetTotalCurrency() + playerInventory.GetCurrency()));
	newBalance.setPosition(Alignment::GetCenterOffset(newBalance.getGlobalBounds().width, cWorldWidth / 2.f), 300.f);
}

void ScoreMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(gotoShopButton.Update(elapsed, input))
	{
		playerInventory.AddCurrency(playerScore.GetTotalCurrency());
		manager.PushGamemode(new ShopMode(resourceCache, manager, playerInventory));
		return;
	}

	background.Update(elapsed);
}

ScoreMode::ScoreMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Score & score, const Player::Inventory & inventory)
	:	Gamemode(resourceCacheRef, managerRef),
	playerScore(score),
	playerInventory(inventory),
	backgroundTexture(),
	navigationButtonTexture(),
	background(),
	gotoShopButton(),
	title(),
	currencyEarned(),
	newBalance()
{
}
