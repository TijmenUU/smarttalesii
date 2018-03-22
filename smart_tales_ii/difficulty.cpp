#include "difficulty.hpp"
#include "platform.hpp"

#include <algorithm>
#include <array>
#include <sstream>
#include <stdexcept>

enum class DifficultyProperty
{
	Unknown = -1,
	StartVelocity,
	VelocityIncrement,
	MaxVelocity,
	HintBorder
};

const std::array<std::string, 5> cDifficultyProperties =
{
	"start-velocity",
	"velocity-increment",
	"max-velocity",
	"hint-border"
};

DifficultyProperty ToDifficultyProperty(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	for(size_t i = 0; i < cDifficultyProperties.size(); ++i)
	{
		if(s.compare(cDifficultyProperties[i]) == 0)
		{
			return static_cast<DifficultyProperty>(i);
		}
	}

	return DifficultyProperty::Unknown;
}

float Difficulty::GetStartScrollVelocity() const
{
	return startVelocity;
}

float Difficulty::GetScrollIncrementVelocity() const
{
	return incrementVelocity;
}

float Difficulty::GetMaxScrollVelocity() const
{
	return maxVelocity;
}

float Difficulty::GetHintBorderXCoord() const
{
	return hintBorderX;
}

void Difficulty::LoadFromFile(const std::string & definitionFile)
{
	std::vector<std::string> lines = Platform::LoadTextFile(definitionFile, true, true);
	
	for(size_t i = 0; i < lines.size(); ++i)
	{
		auto & line = lines[i];
		std::stringstream ss;
		ss.str(line);

		std::string key;
		ss >> key;
		const DifficultyProperty property = ToDifficultyProperty(key);
		switch(property)
		{
			case DifficultyProperty::StartVelocity:
			ss >> startVelocity;
			break;

			case DifficultyProperty::VelocityIncrement:
			ss >> incrementVelocity;
			break;

			case DifficultyProperty::MaxVelocity:
			ss >> maxVelocity;
			break;

			case DifficultyProperty::HintBorder:
			ss >> hintBorderX;
			break;

			default:
			case DifficultyProperty::Unknown:
			break;
		}
	}
}
