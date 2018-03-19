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
	
	Animation::Sheet backgroundSheet, navigationButtonSheet;
	std::unique_ptr<Animation::Sprite> backgroundSprite;
	std::unique_ptr<TextButton> gotoShopButton;
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
