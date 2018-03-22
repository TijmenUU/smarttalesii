#pragma once
#include "animatedsprite.hpp"
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
	TextButton gotoShopButton;
	sf::Text title, currencyEarned, newBalance;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	bool SurpressUpdate() const override;

	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ScoreMode(const Player::Score & score, 
		const Player::Inventory & inventory);
};
