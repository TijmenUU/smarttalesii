#pragma once
#include "animatedsprite.hpp"
#include "currencydisplayer.hpp"
#include "textbutton.hpp"
#include "gamemode.hpp"
#include "playerscore.hpp"
#include "playerinventory.hpp"

#include <memory>

class ScoreMode : public Gamemode
{
private:
	const Player::Score playerScore;
	Player::Inventory playerInventory;
	
	Animation::Sprite backgroundSprite;
	sf::Text gameOverText;
	CurrencyDisplayer earnedCurrency, balanceCurrency;
	TextButton gotoShopButton;
	float animationTimeOut = 0.f;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	void OnEnter() override;

public:
	bool SurpressUpdate() const override;

	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ScoreMode(const Player::Score & score, 
		const Player::Inventory & inventory,
		const std::string & gameOverMsg);
};
