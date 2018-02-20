#include "playerinventory.hpp"

bool Player::Inventory::HasSensorUpgrade(const Upgrade::Sensor s) const
{
	return sensorUpgrades & static_cast<uint8_t>(s);
}

bool Player::Inventory::CanAfford(const unsigned int amount) const
{
	return amount <= currency;
}

void Player::Inventory::AddSensorUpgrade(const Upgrade::Sensor s)
{
	sensorUpgrades |= static_cast<uint8_t>(s);
}

void Player::Inventory::RemoveSensorUpgrade(const Upgrade::Sensor s)
{
	sensorUpgrades &= ~(static_cast<uint8_t>(s));
}

unsigned int Player::Inventory::GetCurrency() const
{
	return currency;
}

void Player::Inventory::AddCurrency(const unsigned int amount)
{
	currency += amount;
}

void Player::Inventory::RemoveCurrency(const unsigned int amount)
{
	// underflow
	if(currency - amount > currency)
	{
		currency = 0;
		return;
	}
	currency -= amount;
}

void Player::Inventory::Reset()
{
	sensorUpgrades = 0U;
	currency = 0U;
}

Player::Inventory::Inventory()
	: sensorUpgrades(0),
	currency(0)
{
}
