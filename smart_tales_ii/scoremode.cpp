#include "scoremode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "shopmode.hpp"

void ScoreMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroundSprite, states);
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
	GameManager::GetInstance().PushGamemode(new UIOverlay(false));

	auto & cache = ResourceCache::GetInstance();
	sf::Font & font = cache.GetFont("commodore");

	backgroundSprite.setPosition(0.f, 0.f);
	backgroundSprite.setScale(4.f, 4.f);
	backgroundSprite.SetAnimation("zoom");

	gotoShopButton.SetPosition(sf::Vector2f(Alignment::GetCenterOffset(gotoShopButton.GetGlobalbounds().width, cWorldWidth / 2.f), cWorldHeight - 120.f));
	sf::Text buttonText("Go to shop", font, 30U);
	buttonText.setOutlineThickness(1.f);
	buttonText.setOutlineColor(sf::Color(120, 63, 0));
	buttonText.setFillColor(sf::Color(181, 105, 0));
	gotoShopButton.SetText(buttonText);

	title.setFont(font);
	title.setCharacterSize(36);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.f);
	title.setString("Score Screen");
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 0.f);

	currencyEarned.setFont(font);
	currencyEarned.setCharacterSize(24);
	currencyEarned.setFillColor(sf::Color::White);
	currencyEarned.setOutlineColor(sf::Color::Black);
	currencyEarned.setOutlineThickness(1.f);
	currencyEarned.setString("Currency earned: " + std::to_string(playerScore.GetTotalCurrency()));
	currencyEarned.setPosition(Alignment::GetCenterOffset(currencyEarned.getGlobalBounds().width, cWorldWidth / 2.f), 200.f);

	newBalance.setFont(font);
	newBalance.setCharacterSize(24);
	newBalance.setFillColor(sf::Color::White);
	newBalance.setOutlineColor(sf::Color::Black);
	newBalance.setOutlineThickness(1.f);
	newBalance.setString("Your new balance: " + std::to_string(playerScore.GetTotalCurrency() + playerInventory.GetCurrency()));
	newBalance.setPosition(Alignment::GetCenterOffset(newBalance.getGlobalBounds().width, cWorldWidth / 2.f), 300.f);
}

void ScoreMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(gotoShopButton.HandleInput(input))
	{
		playerInventory.AddCurrency(playerScore.GetTotalCurrency());
		GameManager::GetInstance().PushGamemode(new ShopMode(playerInventory));
		return;
	}

	backgroundSprite.Update(elapsed);
}

ScoreMode::ScoreMode(const Player::Score & score, const Player::Inventory & inventory)
	:	playerScore(score),
	playerInventory(inventory),
	backgroundSprite(ResourceCache::GetInstance().GetSpriteSheet("scorebackground")),
	gotoShopButton(ResourceCache::GetInstance().GetSpriteSheet("navigationbutton_large"))
{
}
