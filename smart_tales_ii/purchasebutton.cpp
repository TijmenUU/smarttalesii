#include "purchasebutton.hpp"

#include "resourcecache.hpp"

void PurchaseButton::SetPurchased()
{
	Disable();
	SetAnimation("bought");
	isPurchased = true;
}

Upgrade::Sensor PurchaseButton::GetUpgrade() const
{
	return upgrade;
}

unsigned int PurchaseButton::GetPrice() const
{
	return price;
}

bool PurchaseButton::IsPurchased() const
{
	return isPurchased;
}

void PurchaseButton::Refresh(const Player::Inventory & inventory)
{
	if(inventory.HasSensorUpgrade(upgrade))
	{
		SetPurchased();
	}
	else if(!inventory.CanAfford(price))
	{
		Disable();
		SetAnimation("too-expensive");
	}
	else
	{
		Enable();
		SetAnimation("buy");
	}
}

bool PurchaseButton::HandleInput(const Inputhandler & input)
{
	if(Interacts(input))
	{
		SetPurchased();
		return true;
	}

	return false;
}

PurchaseButton::PurchaseButton(const Upgrade::Sensor upgradeToSell,
	const unsigned int sellingPrice)
	: Button(ResourceCache::GetInstance().GetSpriteSheet("purchasebutton")),
	upgrade(upgradeToSell),
	price(sellingPrice)
{
}
