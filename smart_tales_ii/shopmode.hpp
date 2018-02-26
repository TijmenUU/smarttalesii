#pragma once
#include "gamemode.hpp"

#include "playerinventory.hpp"

class ShopMode : public Gamemode
{
private:
	Player::Inventory playerInventory;

	sf::Text title;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Load() override;
	void Update(const sf::Time & timeElapsed, const Inputhandler & input) override;

	ShopMode(Fonts & fontsRef, GameManager & managerRef, const Player::Inventory & inventory);
	~ShopMode() override = default;
};
