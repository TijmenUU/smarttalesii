#include "scoremode.hpp"

ScoreMode::ScoreMode(Fonts & fontsRef, GameManager & managerRef, const Player::Score & score, const Player::Inventory & inventory)
	:	Gamemode(fontsRef, managerRef),
	playerScore(score),
	playerInventory(inventory)
{
	playerInventory.AddCurrency(score.GetCurrency());
}
