#include "../../util/platform.hpp"
#include "../../util/string.hpp"
#include "animationsheet.hpp"
#include <array>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace Animation
{
	Animation::Animation()
		: frameStart(),
		frameSize(),
		frameMargin(0U),
		frameCount(0U),
		frameTime(0U),
		reverse(false),
		loop(false)
	{
	}

#pragma region Animation Loading
	std::array<std::string, 8> cAnimationHeaders =
	{
		"spritesheet-source",
		"animation"
	};

	enum class AnimationHeader
	{
		Unknown = -1,
		SpritesheetSource,
		Animation
	};

	AnimationHeader GetHeader(std::string headerstr)
	{
		std::transform(headerstr.begin(), headerstr.end(), headerstr.begin(), ::tolower);
		for(size_t i = 0; i < cAnimationHeaders.size(); ++i)
		{
			if(cAnimationHeaders[i].compare(headerstr) == 0)
			{
				return static_cast<AnimationHeader>(i);
			}
		}

		return AnimationHeader::Unknown;
	}

	std::array<std::string, 9> cAnimationProperties =
	{
		"frame-start-x",
		"frame-start-y",
		"frame-width",
		"frame-height",
		"frame-margin",
		"frame-count",
		"frame-time",
		"reverse",
		"loop"
	};

	enum class AnimationProperty
	{
		Unknown = -1,
		FrameStartX,
		FrameStartY,
		FrameWidth,
		FrameHeight,
		FrameMargin,
		FrameCount,
		FrameTime,
		Reverse,
		Loop
	};

	AnimationProperty GetProperty(std::string propertystr)
	{
		std::transform(propertystr.begin(), propertystr.end(), propertystr.begin(), ::tolower);
		for(size_t i = 0; i < cAnimationProperties.size(); ++i)
		{
			if(cAnimationProperties[i].compare(propertystr) == 0)
			{
				return static_cast<AnimationProperty>(i);
			}
		}

		return AnimationProperty::Unknown;
	}

	Animation LoadAnimation(const std::vector<std::string> & definition, size_t & i)
	{
		Animation result;
		while(i < definition.size() && definition[i][0] == '\t')
		{
			std::stringstream ss;
			ss.str(definition[i]);

			std::string key;
			ss >> key;
			const auto property = GetProperty(key);

			switch(property)
			{
				case AnimationProperty::FrameStartX:
				ss >> result.frameStart.x;
				break;

				case AnimationProperty::FrameStartY:
				ss >> result.frameStart.y;
				break;

				case AnimationProperty::FrameWidth:
				ss >> result.frameSize.x;
				break;

				case AnimationProperty::FrameHeight:
				ss >> result.frameSize.y;
				break;

				case AnimationProperty::FrameMargin:
				ss >> result.frameMargin;
				break;

				case AnimationProperty::FrameCount:
				ss >> result.frameCount;
				break;

				case AnimationProperty::FrameTime:
				ss >> result.frameTime;
				break;

				case AnimationProperty::Reverse:
				result.reverse = true;
				break;

				case AnimationProperty::Loop:
				result.loop = true;
				break;

				default:
				break;
			}

			++i;
		}

		return result;
	}
#pragma endregion
	
	void Sheet::LoadFromFile(const std::string & animationFile)
	{
		auto lines = Util::LoadTextFile(animationFile, true, true);

		for(size_t i = 0U; i < lines.size(); ++i)
		{
			std::stringstream ss;
			ss.str(lines[i]);

			std::string key;
			ss >> key;

			const auto header = GetHeader(key);
			switch(header)
			{
				case AnimationHeader::SpritesheetSource:
				{
					const auto sourcefile = Util::GetStringInQuotes(lines[i]);
					if(!texture.loadFromFile(sourcefile))
					{
						throw std::runtime_error("Failed to load texture <" + sourcefile + "> specified in animation file <" + animationFile + ">.");
					}
				}
				break;

				case AnimationHeader::Animation:
				{
					std::string value;
					ss >> value;

					++i;
					animations[value] = LoadAnimation(lines, i);
					--i; // decrement once because next loop we should consider that position
				}
				break;

				default:
				break;
			}
		}
	}

	sf::IntRect Sheet::GetFrame(const Animation & anim, const unsigned int frameNumber) const
	{
		assert(frameNumber < anim.frameCount);
		
		return sf::IntRect(anim.frameStart.x + frameNumber * anim.frameSize.x, 
			anim.frameStart.y, 
			anim.frameSize.x, 
			anim.frameSize.y);
	}

	const Animation * Sheet::GetAnimation(const std::string & name) const
	{
		auto findresult = animations.find(name);
		if(findresult == animations.end())
		{
			return nullptr;
		}
		return &(findresult->second);
	}

	std::string Sheet::GetAnimationName(const Animation * ptr) const
	{
		for(auto & pair : animations)
		{
			if(&(pair.second) == ptr)
			{
				return pair.first;
			}
		}

		return std::string();
	}

	const sf::Texture & Sheet::GetTexture() const
	{
		return texture;
	}
}
