#pragma once
#include "obstacletype.hpp"
#include "upgrades.hpp"

namespace Player
{
	class Inventory
	{
	private:
		uint8_t sensorUpgrades = 0U;
		unsigned int currency = 0U;

	public:
		bool HasSensorUpgrade(const Upgrade::Sensor s) const;
		bool CanAfford(const unsigned int amount) const;

		void AddSensorUpgrade(const Upgrade::Sensor s);
		void RemoveSensorUpgrade(const Upgrade::Sensor s);

		bool HasObstacleCounter(const Obstacle::Type o) const;
		unsigned int GetSensorUpgradeCount() const;

		unsigned int GetCurrency() const;
		void AddCurrency(const unsigned int amount);
		void RemoveCurrency(const unsigned int amount);

		void Reset();
	};
}
