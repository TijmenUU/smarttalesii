/*
	obstacletype.hpp

	Utility methods and the definition of all different
	obstacle types that exist.

	The displayed hint strings in the RunningMode gamemode
	are defined in the cpp file.
*/

#pragma once

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
}
