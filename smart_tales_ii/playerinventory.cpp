#include "playerinventory.hpp"

#include <cassert>

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

bool Player::Inventory::HasObstacleCounter(const Obstacle::Type o) const
{
	const auto requiredSensorUpgrade = Upgrade::GetCounteringSensor(o);
	assert(o != Obstacle::Type::Unknown && requiredSensorUpgrade != Upgrade::Sensor::Unknown);
	
	return sensorUpgrades & static_cast<uint8_t>(requiredSensorUpgrade);
}

unsigned int Player::Inventory::GetSensorUpgradeCount() const
{
	const int size = sizeof(sensorUpgrades) * 8; // get bit count
	unsigned int count = 0U;
	for(unsigned int i = 0U; i < size; ++i)
	{
		if((1U << i) & sensorUpgrades)
		{
			++count;
		}
	}

	return count;
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
