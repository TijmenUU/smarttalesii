#include "difficulty.hpp"
#include "platform.hpp"

#include <algorithm>
#include <array>
#include <sstream>
#include <stdexcept>

#include <iostream> // debug

enum class DifficultyProperty
{
	Unknown = -1,
	StartVelocity,
	VelocityControl,
	MaxVelocity,
	HintBorder,
	VelocityIncrementPerUpgrade,
};

const std::array<std::string, 6> cDifficultyProperties =
{
	"start-velocity",
	"velocity-control",
	"max-velocity",
	"hint-border",
	"velocity-increment-per-upgrade"
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

float Difficulty::GetStartScrollVelocity(const unsigned int upgradeCount) const
{
	return startVelocity + (static_cast<float>(upgradeCount) * speedIncrementPerUpgrade);
}

float Difficulty::GetScrollVelocity(const unsigned int upgradeCount, const float elapsedSeconds) const
{
	const float velocity = GetStartScrollVelocity(upgradeCount) + ((elapsedSeconds * elapsedSeconds) / velocityControl);
	std::cout << "Velocity: " << velocity << '\n'; // debug
	if(velocity > maxVelocity)
	{
		return maxVelocity;
	}

	return velocity;
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

			case DifficultyProperty::VelocityControl:
			ss >> velocityControl;
			break;

			case DifficultyProperty::MaxVelocity:
			ss >> maxVelocity;
			break;

			case DifficultyProperty::HintBorder:
			ss >> hintBorderX;
			break;

			case DifficultyProperty::VelocityIncrementPerUpgrade:
			ss >> speedIncrementPerUpgrade;
			break;

			default:
			case DifficultyProperty::Unknown:
			break;
		}
	}
}
