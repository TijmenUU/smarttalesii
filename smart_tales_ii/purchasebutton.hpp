#pragma once
#include "playerinventory.hpp"
#include "textbutton.hpp"
#include "upgrades.hpp"

class PurchaseButton : public TextButton
{
private:
	Upgrade::Sensor upgrade;
	unsigned int price;

	void Purchase();

public:
	void SetUpgrade(const Upgrade::Sensor upgradeToSell);
	void SetPrice(const unsigned int upgradePrice);

	Upgrade::Sensor GetUpgrade() const;
	unsigned int GetPrice() const;

	void Refresh(const Player::Inventory & inventory);

	bool HandleInput(const Inputhandler & input) override;

	PurchaseButton(const Animation::Sheet & sheetRef);
};
