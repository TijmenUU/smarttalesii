#pragma once
#include "upgrades.hpp"

namespace Player
{
	class Inventory
	{
	private:
		uint8_t sensorUpgrades;
		unsigned int currency;

	public:
		bool HasSensorUpgrade(const Upgrade::Sensor s) const;
		bool CanAfford(const unsigned int amount) const;

		void AddSensorUpgrade(const Upgrade::Sensor s);
		void RemoveSensorUpgrade(const Upgrade::Sensor s);

		unsigned int GetCurrency() const;
		void AddCurrency(const unsigned int amount);
		void RemoveCurrency(const unsigned int amount);

		void Reset();

		Inventory();
	};
}
