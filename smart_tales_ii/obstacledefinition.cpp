#include "obstacledefinition.hpp"
#include "gesture.hpp"
#include "platform.hpp"
#include "stringutil.hpp"

#include <array>
#include <sstream>

enum class ObstacleProperty
{
	Unknown = -1,
	Type,
	AnimationFile,
	InteractionRadius,
	MinimalInteractionDistance,
	NeutralizationGestures,
	InteractionLocalPosition,
	HintLocalPosition,
	HintString
};

std::array<std::string, 8U> cObstaclePropertyStrings = 
{
	"type",
	"animation-file",
	"interaction-radius",
	"minimal-interaction-distance",
	"neutralization-gestures",
	"interaction-local-position",
	"hint-local-position",
	"hint-string"
};

ObstacleProperty ToObstacleProperty(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower); // to lower case
	for(size_t i = 0; i < cObstaclePropertyStrings.size(); ++i)
	{
		if(s.compare(cObstaclePropertyStrings[i]) == 0)
		{
			// remember to cast to powers of two (see enum definition in header)
			return static_cast<ObstacleProperty>(i);
		}
	}

	return ObstacleProperty::Unknown;
}

const std::array<std::string, 4U> cObstacleStringTypes =
{
	"furniture",
	"door",
	"light",
	"phone"
};

ObstacleType ToObstacleType(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower); // to lower case
	for(size_t i = 0; i < cObstacleStringTypes.size(); ++i)
	{
		if(s.compare(cObstacleStringTypes[i]) == 0)
		{
			return static_cast<ObstacleType>(i);
		}
	}

	return ObstacleType::Unknown;
}

void ObstacleDefinition::LoadFromFile(const std::string & filename)
{
	const auto lines = Platform::LoadTextFile(filename, true, true);

	for(size_t i = 0; i < lines.size(); ++i)
	{
		const auto & line = lines[i];

		std::stringstream ss;
		ss.str(line);

		std::string key;
		ss >> key;
		ObstacleProperty property = ToObstacleProperty(key);
		switch(property)
		{
			case ObstacleProperty::Type:
			{
				std::string value;
				ss >> value;

				type = ToObstacleType(value);
			}
			break;

			case ObstacleProperty::AnimationFile:
			animatedSprite.LoadFromFile(Util::GetStringInQuotes(line), texture);
			break;

			case ObstacleProperty::InteractionRadius:
			ss >> interactionRadius;
			break;

			case ObstacleProperty::MinimalInteractionDistance:
			ss >> minimalDistance;
			break;

			case ObstacleProperty::NeutralizationGestures:
			{
				std::string value;
				while(ss >> value)
				{
					SwipeType s = ToSwipeType(value);
					neutralizationSwipes |= static_cast<uint8_t>(s);
				}		
			}
			break;

			case ObstacleProperty::InteractionLocalPosition:
			ss >> interactionLocalPos.x;
			ss >> interactionLocalPos.y;
			break;

			case ObstacleProperty::HintLocalPosition:
			ss >> neutralizationHintLocalPos.x;
			ss >> neutralizationHintLocalPos.y;
			break;

			case ObstacleProperty::HintString:
			neutralizationHint = Util::GetStringInQuotes(line);
			break;

			default:
			case ObstacleProperty::Unknown:
			break;
		}
	}

	if(type == ObstacleType::Unknown)
	{
		throw std::runtime_error("Error loading <" + filename + ">: result is of unknown type.");
	}
}

ObstacleDefinition::ObstacleDefinition()
	: type(ObstacleType::Unknown),
	texture(),
	animatedSprite(),
	interactionLocalPos(0.f, 0.f),
	neutralizationHintLocalPos(0.f, 0.f),
	interactionRadius(0.f),
	minimalDistance(0.f),
	neutralizationSwipes(0U),
	neutralizationHint()
{
}