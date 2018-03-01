#include "upgrades.hpp"

#include "stringutil.hpp"

#include <algorithm>
#include <array>
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

	ObstacleType GetObstacleCounter(const Sensor s)
	{
		switch(s)
		{
			case Sensor::PassiveInfrared:
			return ObstacleType::Light;

			case Sensor::ActiveInfrared:
			return ObstacleType::Door;

			case Sensor::HealthBand:
			return ObstacleType::Phone;

			case Sensor::LiveTile:
			return ObstacleType::Furniture;

			case Sensor::Unknown:
			default:
			return ObstacleType::Unknown;
		}
	}

	Sensor GetCounteringSensor(const ObstacleType t)
	{
		switch(t)
		{
			case ObstacleType::Light:
			return Sensor::PassiveInfrared;

			case ObstacleType::Door:
			return Sensor::ActiveInfrared;
			
			case ObstacleType::Phone:
			return Sensor::HealthBand;

			case ObstacleType::Furniture:
			return Sensor::LiveTile;

			case ObstacleType::Unknown:
			default:
			return Sensor::Unknown;
		}
	}
}
