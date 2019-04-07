#include <algorithm>
#include <array>
#include "upgrades.hpp"
#include <utility>

namespace Upgrade
{
	std::array<std::string, 4> cSensorStrings =
	{
		"passiveinfrared",
		"activeinfrared",
		"healthband",
		"livetile"
	};

	Sensor ToEnum(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		for(size_t i = 0; i < cSensorStrings.size(); ++i)
		{
			if(cSensorStrings[i].compare(str) == 0)
			{
				return static_cast<Sensor>(i + 1);
			}
		}
		return Sensor::Unknown;
	}

	Obstacle::Type GetObstacleCounter(const Sensor s)
	{
		switch(s)
		{
			case Sensor::PassiveInfrared:
			return Obstacle::Type::Light;

			case Sensor::ActiveInfrared:
			return Obstacle::Type::Door;

			case Sensor::HealthBand:
			return Obstacle::Type::Phone;

			case Sensor::LiveTile:
			return Obstacle::Type::Furniture;

			case Sensor::Unknown:
			default:
			return Obstacle::Type::Unknown;
		}
	}

	Sensor GetCounteringSensor(const Obstacle::Type t)
	{
		switch(t)
		{
			case Obstacle::Type::Light:
			return Sensor::PassiveInfrared;

			case Obstacle::Type::Door:
			return Sensor::ActiveInfrared;
			
			case Obstacle::Type::Phone:
			return Sensor::HealthBand;

			case Obstacle::Type::Furniture:
			return Sensor::LiveTile;

			case Obstacle::Type::Unknown:
			default:
			return Sensor::Unknown;
		}
	}
}
