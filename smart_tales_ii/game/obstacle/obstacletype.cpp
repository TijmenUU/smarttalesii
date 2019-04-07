#include <algorithm>
#include <array>
#include "obstacletype.hpp"

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
		switch(t)
		{
			case Type::Furniture:
			return "Swipe down!";

			case Type::Door:
			return "Swipe left or right!";

			case Type::Light:
			return "Tap the button!";

			case Type::Phone:
			return "Swipe up!";

			default:
			case Type::Unknown:
			return std::string();
		}
	}
}
