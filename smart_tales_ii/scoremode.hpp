#pragma once
#include "gamemode.hpp"
#include "playerscore.hpp"
#include "playerinventory.hpp"

class ScoreMode : public Gamemode
{
private:
	const Player::Score playerScore;
	Player::Inventory playerInventory;

	sf::Text title;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Load() override;
	void Update(const sf::Time & timeElapsed, const Inputhandler & input) override;

	ScoreMode(Fonts & fontsRef, 
		GameManager & managerRef, 
		const Player::Score & score, 
		const Player::Inventory & inventory);
	~ScoreMode() override = default;
};
