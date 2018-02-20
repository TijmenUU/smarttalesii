#include "shopmode.hpp"

ShopMode::ShopMode(Fonts & fontsRef, GameManager & managerRef, const Player::Inventory & inventory)
	:Gamemode(fontsRef, managerRef),
	playerInventory(inventory)
{
}
