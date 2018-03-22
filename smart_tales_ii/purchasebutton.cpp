#include "purchasebutton.hpp"

void PurchaseButton::Purchase()
{
	Disable();
	SetAnimation("bought");
	SetString("Bought");
}

void PurchaseButton::SetUpgrade(const Upgrade::Sensor upgradeToSell)
{
	upgrade = upgradeToSell;
}

void PurchaseButton::SetPrice(const unsigned int upgradePrice)
{
	price = upgradePrice;
}

Upgrade::Sensor PurchaseButton::GetUpgrade() const
{
	return upgrade;
}

unsigned int PurchaseButton::GetPrice() const
{
	return price;
}

void PurchaseButton::Refresh(const Player::Inventory & inventory)
{
	if(inventory.HasSensorUpgrade(upgrade))
	{
		Purchase();
	}
	else if(!inventory.CanAfford(price))
	{
		Disable();
		SetAnimation("too-expensive");
		SetString("Can't\nafford");
	}
	else
	{
		Enable();
		SetAnimation("buy");
		SetString("Buy");
	}
}

bool PurchaseButton::HandleInput(const Inputhandler & input)
{
	if(isEnabled && Interacts(input))
	{
		Purchase();
		return true;
	}

	return false;
}

PurchaseButton::PurchaseButton(const Animation::Sheet & sheetRef)
	: TextButton(sheetRef)
{
}
