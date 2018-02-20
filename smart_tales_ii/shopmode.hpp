#pragma once
#include "gamemode.hpp"
#include "playerinventory.hpp"

class ShopMode : public Gamemode
{
private:
	Player::Inventory playerInventory;

public:
	ShopMode(Fonts & fontsRef, GameManager & managerRef, const Player::Inventory & inventory);
	~ShopMode() override = default;
};
