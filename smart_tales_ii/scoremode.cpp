#include "scoremode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "shopmode.hpp"

const float cAnimationTimeOut = 4.f;

void ScoreMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroundSprite, states);

	if(backgroundSprite.IsAnimationFinished())
	{
		target.draw(gameOverText, states);
		target.draw(earnedCurrency, states);
		target.draw(balanceCurrency, states);
		target.draw(gotoShopButton, states);
	}
}

bool ScoreMode::SurpressUpdate() const
{
	return true;
}

void ScoreMode::Setup()
{
	//manager.PopAllBelow(this);
	GameManager::GetInstance().PushGamemode(new UIOverlay(false));

	auto & cache = ResourceCache::GetInstance();
	sf::Font & font = cache.GetFont("commodore");

	backgroundSprite.setPosition(0.f, 0.f);
	backgroundSprite.setScale(4.f, 4.f);
	backgroundSprite.SetAnimation("zoom");

	const float horizontalCenterLine = 800.f;

	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(2.f);
	const auto textBounds = gameOverText.getLocalBounds();
	gameOverText.setPosition(Alignment::GetCenterOffset(textBounds.width, horizontalCenterLine) + textBounds.left, 175.f);

	earnedCurrency.SetValue(0U);
	earnedCurrency.CenterOn(horizontalCenterLine, 300.f);

	balanceCurrency.SetValue(playerScore.GetTotalCurrency() + playerInventory.GetCurrency());
	balanceCurrency.CenterOn(horizontalCenterLine, 350.f);

	gotoShopButton.SetPosition(sf::Vector2f(Alignment::GetCenterOffset(gotoShopButton.GetGlobalbounds().width, cWorldWidth / 2.f), cWorldHeight - 120.f));
	sf::Text buttonText("Go to shop", font, 30U);
	buttonText.setOutlineThickness(2.f);
	buttonText.setOutlineColor(sf::Color(120, 63, 0));
	buttonText.setFillColor(sf::Color::White);
	gotoShopButton.SetText(buttonText);
}

void ScoreMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	backgroundSprite.Update(elapsed);

	if(backgroundSprite.IsAnimationFinished())
	{
		if(gotoShopButton.HandleInput(input))
		{
			playerInventory.AddCurrency(playerScore.GetTotalCurrency());
			GameManager::GetInstance().PushGamemode(new ShopMode(playerInventory));
			return;
		}

		if(animationTimeOut < cAnimationTimeOut)
			animationTimeOut += elapsed.asSeconds();
		else
		{
			earnedCurrency.Update(elapsed);
			balanceCurrency.Update(elapsed);
		}
	}
}

ScoreMode::ScoreMode(const Player::Score & score, 
	const Player::Inventory & inventory, 
	const std::string & gameOverMsg)
	:	playerScore(score),
	playerInventory(inventory),
	backgroundSprite(ResourceCache::GetInstance().GetSpriteSheet("scorebackground")),
	gameOverText(gameOverMsg, ResourceCache::GetInstance().GetFont("commodore"), 36),
	earnedCurrency(5U, "Currency earned: ", score.GetTotalCurrency(), false),
	balanceCurrency(5U, "Balance: ", inventory.GetCurrency(), false),
	gotoShopButton(ResourceCache::GetInstance().GetSpriteSheet("navigationbutton_large"))
{
}
