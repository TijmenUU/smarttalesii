#pragma once
#include "animatedsprite.hpp"

namespace Obstacle
{
	enum class Type
	{
		Unknown = -1,
		Furniture,
		Door,
		Light,
		Phone
	};

	Type GetType(std::string s);

	std::string GetString(const Type t);

	std::string GetHintString(const Type t);

	std::string GetGameOverString(const Type t);
}
