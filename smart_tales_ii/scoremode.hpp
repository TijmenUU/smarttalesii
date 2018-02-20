#pragma once
#include "gamemode.hpp"
#include "playerscore.hpp"
#include "playerinventory.hpp"

class ScoreMode : public Gamemode
{
private:
	const Player::Score playerScore;
	Player::Inventory playerInventory;

public:
	ScoreMode(Fonts & fontsRef, GameManager & managerRef, const Player::Score & score, const Player::Inventory & inventory);
	~ScoreMode() override = default;
};
