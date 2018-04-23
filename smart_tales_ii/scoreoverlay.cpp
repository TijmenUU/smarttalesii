#include "scoreoverlay.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "shopmode.hpp"

const float cAnimationTimeOut = 4.f;

void ScoreOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
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

void ScoreOverlay::OnEnter()
{
	SoundManager::GetInstance().SetMusicVolume(50.f);
}

bool ScoreOverlay::SurpressUpdate() const
{
	return true;
}

void ScoreOverlay::Setup()
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
	//gameOverText.setOutlineColor(sf::Color::Black);
	//gameOverText.setOutlineThickness(2.f);
	const auto textBounds = gameOverText.getLocalBounds();
	gameOverText.setPosition(Alignment::GetCenterOffset(textBounds.width, horizontalCenterLine) + textBounds.left, 100.f);

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

void ScoreOverlay::Update(const sf::Time & elapsed, const Inputhandler & input)
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

// helper function
std::string GetGameOverMsg(const Obstacle::Type cause)
{
	const static std::array<std::string, 5> messages = {
		"Small accidents are scary!\n96 000 elderly had to visit\nthe emergency after one.", // Cijferrapportage Valongevallen 65 jaar en ouder, 2016
		"Ouch! Tripping over accounts\nfor 23% of the elderly visiting\nthe emergency room.", // Cijferrapportage Valongevallen 65 jaar en ouder, 2016
		"Practice makes perfect!\nNobody likes sitting still at\nhome.", // AAL Forum 2016: elderly want to have an active part in society
		"Tech up! Simple aids\nare here to help.", // The elderly are afraid of using IT systems, KLEINBERGER et al 2007
		"Big brother is watching?\nNot really, most simple sensors\noperate on their own!" // Privacy, Identity and Security in Ambient Intelligence, Friedewald et al 2005
	};
	static unsigned int idx = 0U;

	if(idx >= messages.size())
	{
		idx = 0U;
	}

	return messages[idx++];
}

ScoreOverlay::ScoreOverlay(const Player::Score & score, 
	const Player::Inventory & inventory, 
	const Obstacle::Type gameOverCause)
	:	playerScore(score),
	playerInventory(inventory),
	backgroundSprite(ResourceCache::GetInstance().GetSpriteSheet("scorebackground")),
	gameOverText(GetGameOverMsg(gameOverCause), ResourceCache::GetInstance().GetFont("commodore"), 36),
	earnedCurrency(5U, "Currency earned: ", score.GetTotalCurrency(), true),
	balanceCurrency(5U, "Balance: ", inventory.GetCurrency(), true),
	gotoShopButton(ResourceCache::GetInstance().GetSpriteSheet("navigationbutton_large"))
{
}
