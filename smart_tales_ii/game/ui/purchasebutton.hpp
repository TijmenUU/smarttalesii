/*
	purchasebutton.hpp

	Specialized button that holds the upgrade unlock logic.

	Only used by the upgradetile from the carousel in the shop
	gamemode.
*/

#pragma once
#include "../player/playerinventory.hpp"
#include "../player/upgrades.hpp"
#include "button.hpp"

class PurchaseButton : public Button
{
private:
	Upgrade::Sensor upgrade;
	unsigned int price;
	bool isPurchased = false;

	void SetPurchased();

public:
	Upgrade::Sensor GetUpgrade() const;
	unsigned int GetPrice() const;
	bool IsPurchased() const;

	void Refresh(const Player::Inventory & inventory);

	bool HandleInput(const Inputhandler & input) override;

	PurchaseButton(const Upgrade::Sensor upgradeToSell,
		const unsigned int sellingPrice);
};
