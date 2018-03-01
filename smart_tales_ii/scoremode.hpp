#pragma once
#include "textbutton.hpp"
#include "gamemode.hpp"
#include "playerscore.hpp"
#include "playerinventory.hpp"

class ScoreMode : public Gamemode
{
private:
	const Player::Score playerScore;
	Player::Inventory playerInventory;
	
	sf::Texture navigationButtonTexture;
	TextButton gotoShopButton;
	sf::Text title, playerScoreTxt, currencyEarned, newBalance;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ScoreMode(ResourceCache & resourceCacheRef, 
		GameManager & managerRef, 
		const Player::Score & score, 
		const Player::Inventory & inventory);
};
