/*
	scoreoverlay.hpp

	A score overlay for the gameover event in RunningMode.
	It shows the player currency gained, some information
	on AAL and provides a button to go to the shop.

	It does not surpress the update of underlying gamemodes
	It does not surpress the drawing of underlying gamemodes
*/

#pragma once
#include "animatedsprite.hpp"
#include "currencydisplayer.hpp"
#include "gamemode.hpp"
#include "gameovermessage.hpp"
#include "playerscore.hpp"
#include "playerinventory.hpp"
#include "textbutton.hpp"

#include <memory>

class ScoreOverlay : public Gamemode
{
private:
	const Player::Score playerScore;
	Player::Inventory playerInventory;
	
	Animation::Sprite backgroundSprite;
	GameoverMessage gameoverMsg;
	CurrencyDisplayer earnedCurrency, balanceCurrency;
	TextButton gotoShopButton;
	float animationTimeOut = 0.f;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	void OnEnter() override;

public:
	bool SuppressUpdate() const override;

	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ScoreOverlay(const Player::Score & score,
		const Player::Inventory & inventory,
		const Obstacle::Type gameOverCause);
};
