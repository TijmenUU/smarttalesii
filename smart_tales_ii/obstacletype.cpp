#include "obstacletype.hpp"

#include <algorithm>
#include <array>

// TODO remove if unused

namespace Obstacle
{
	const std::array<std::string, 4> cTypeNames = {
		"furniture",
		"door",
		"light",
		"phone"
	};

	Type GetType(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(), ::tolower); // TODO make sure this is cross platform compatible?
		const auto fresult = std::find(cTypeNames.begin(), cTypeNames.end(), s);
		if(fresult == cTypeNames.end())
		{
			return Type::Unknown;
		}

		return static_cast<Type>(fresult - cTypeNames.begin());
	}

	std::string GetString(const Type t)
	{
		const auto index = static_cast<int>(t);
		if(index < 0)
		{
			return "";
		}
		return cTypeNames[index];
	}

	std::string GetHintString(const Type t)
	{
		return std::string();
	}
}
