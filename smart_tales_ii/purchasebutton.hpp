#pragma once
#include "playerinventory.hpp"
#include "button.hpp"
#include "upgrades.hpp"

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
		const unsigned int sellingPrice,
		const Animation::Sheet & sheetRef);
};
