#pragma once
#include "animatedsprite.hpp"
#include "textbutton.hpp"
#include "gamemode.hpp"
#include "playerscore.hpp"
#include "playerinventory.hpp"

class ScoreMode : public Gamemode
{
private:
	const Player::Score playerScore;
	Player::Inventory playerInventory;
	
	sf::Texture backgroundTexture, navigationButtonTexture;
	AnimatedSprite background;
	TextButton gotoShopButton;
	sf::Text title, currencyEarned, newBalance;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	bool SurpressUpdate() const override;

	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ScoreMode(ResourceCache & resourceCacheRef, 
		GameManager & managerRef, 
		const Player::Score & score, 
		const Player::Inventory & inventory);
};
