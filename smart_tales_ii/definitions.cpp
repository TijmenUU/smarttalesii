#include "definitions.hpp"
#include "platform.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <locale>
#include <sstream>

namespace Definition
{
	const std::array<std::string, 7U> SwipeStringTypes =
	{
		"tap",
		"upwards",
		"downwards",
		"leftwards",
		"rightwards"
	};

	SwipeType ToSwipeType(std::string value)
	{
		std::transform(value.begin(), value.end(), value.begin(), ::tolower); // to lower case
		for(size_t i = 0; i < SwipeStringTypes.size(); ++i)
		{
			if(value.compare(SwipeStringTypes[i]) == 0)
			{
				// remember to cast to powers of two (see enum definition in header)
				return static_cast<SwipeType>(1U << (i + 1U));
			}
		}

		return SwipeType::None;
	}

	const std::array<std::string, 4U> ObstacleStringTypes = 
	{
		"furniture",
		"door",
		"lightswitch",
		"phone"
	};

	ObstacleType ToObstacleType(std::string value)
	{
		std::transform(value.begin(), value.end(), value.begin(), ::tolower); // to lower case
		for(size_t i = 0; i < ObstacleStringTypes.size(); ++i)
		{
			if(value.compare(ObstacleStringTypes[i]) == 0)
			{
				return static_cast<ObstacleType>(i + 1U);
			}
		}

		return ObstacleType::None;
	}

	std::string ToHint(const ObstacleType o)
	{
		switch(o)
		{
			case ObstacleType::Furniture:
			return "Swipe down!";

			case ObstacleType::Door:
			return "Swipe left or right!";

			case ObstacleType::Lightswitch:
			return "Tap it!";

			case ObstacleType::Phone:
			return "Swipe up!";
			
			default:
			return "";
		}
	}

	Obstacle::Obstacle(const std::string & definitionline)
		: type(ObstacleType::None),
		textureSourceFile(),
		texture(),
		interactionRadius(-1.f),
		minimalDistance(-1.f),
		neutralizationSwipes(0U),
		neutralizationHint()
	{
		std::stringstream ss;
		ss.str(definitionline);

		std::string value;
		ss >> value;
		type = ToObstacleType(value);
		if(type != ObstacleType::None) // if invalid, stop here
		{
			ss >> textureSourceFile;

			ss >> value;
			interactionRadius = std::stoi(value);

			ss >> value;
			minimalDistance = std::stoi(value);

			neutralizationSwipes = 0U;
			while(ss >> value)
			{
				neutralizationSwipes |= static_cast<uint8_t>(ToSwipeType(value));
			}

			neutralizationHint = ToHint(type);
		}

		if(!texture.loadFromFile(textureSourceFile))
		{
			throw std::runtime_error("Error loading texture file <" + textureSourceFile + ">");
		}
		texture.setSmooth(false);
		texture.setRepeated(false);
	}

	std::vector<Obstacle> GetObstacles(const std::string & definitionFile)
	{
		std::vector<std::string> lines;
		try
		{
			lines = Platform::LoadTextFile(definitionFile, true, true);
		}
		catch(std::runtime_error & e)
		{
			throw std::runtime_error(std::string("Error loading obstacles for game due to: ") + e.what());
		}

		std::vector<Obstacle> result;

		for(size_t i = 0; i < lines.size(); ++i)
		{
			auto & line = lines[i];

			result.emplace_back(line);
			if(result.back().type == ObstacleType::None)
			{
				std::cout << "Error parsing obstacle definition line <" << line << ">\n";
				result.pop_back();
			}
		}

		return result;
	}

	Difficulty GetDifficulty(const std::string & definitionFile)
	{
		std::vector<std::string> lines;
		try
		{
			lines = Platform::LoadTextFile(definitionFile, true, true);
		}
		catch(std::runtime_error & e)
		{
			throw std::runtime_error(std::string("Error loading game difficulty settings due to: ") + e.what());
		}

		Difficulty result;

		bool jobDone = false;
		for(size_t i = 0; i < lines.size(); ++i)
		{
			auto & line = lines[i];

			// this line is not empty or a comment, must be our definition line
			std::stringstream ss;
			ss.str(line);

			if(!(ss >> result.startVelocity))
			{
				throw std::runtime_error("Error during difficulty file parsing: start velocity invalid <" + line + ">");
			}
			if(!(ss >> result.incrementInterval))
			{
				throw std::runtime_error("Error during difficulty file parsing: increment interval invalid <" + line + ">");
			}
			if(!(ss >> result.incrementVelocity))
			{
				throw std::runtime_error("Error during difficulty file parsing: increment velocity invalid <" + line + ">");
			}
			if(!(ss >> result.incrementMaxVelocity))
			{
				throw std::runtime_error("Error during difficulty file parsing: increment max velocity invalid <" + line + ">");
			}
			if(!(ss >> result.hintBorderX))
			{
				throw std::runtime_error("Error during difficulty file parsing: hint border x position invalid <" + line + ">");
			}

			jobDone = true;
			break;
		}

		if(!jobDone)
		{
			throw std::runtime_error("Error parsing difficulty file " + definitionFile + ", definition line is missing!");
		}

		return result;
	}
}
