#pragma once
#include <cstdint>

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
}
