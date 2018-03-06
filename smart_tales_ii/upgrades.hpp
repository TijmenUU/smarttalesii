#pragma once
#include "obstacletype.hpp"

#include <cstdint>
#include <string>

namespace Upgrade
{
	enum class Sensor : uint8_t
	{
		Unknown = 0,
		PassiveInfrared = 1,
		ActiveInfrared = 2,
		HealthBand = 4,
		LiveTile = 8
	};

	Sensor ToEnum(std::string str);

	Obstacle::Type GetObstacleCounter(const Sensor s);

	Sensor GetCounteringSensor(const Obstacle::Type t);
}
