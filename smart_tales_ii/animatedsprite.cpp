#include "animatedsprite.hpp"
#include "platform.hpp"

#include <array>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

std::array<std::string, 8> cAnimationHeaders =
{
	"texture-source",
	"animation"
};

enum class AnimationHeader
{
	Unknown = -1,
	TextureSource,
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

Animation::Animation()
	:frameStart(0U, 0U),
	frameSize(0U, 0U),
	frameMargin(0U),
	frameCount(0U),
	frameTime(0U),
	reverse(false),
	loop(false)
{
}

void AnimatedSprite::GetNextFrame()
{
	assert(currentAnimation != nullptr);

	if(currentAnimation->frameCount < 2)
		return;

	++currentFrame;
	if(currentFrame >= currentAnimation->frameCount)
	{
		if(!currentAnimation->loop)
		{
			currentFrame = currentAnimation->frameCount;
		}
		else
		{
			currentFrame = 0;
			setTextureRect(sf::IntRect(
				currentAnimation->frameStart.x,
				currentAnimation->frameStart.y,
				currentAnimation->frameSize.x,
				currentAnimation->frameSize.y));
		}
	}
	else
	{
		auto textureRect = getTextureRect();
		if(currentAnimation->reverse)
		{
			textureRect.left -= currentAnimation->frameMargin + currentAnimation->frameSize.x;
		}
		else
		{
			textureRect.left += currentAnimation->frameMargin + currentAnimation->frameSize.x;
		}

		setTextureRect(textureRect);
	}
}

std::vector<std::string> AnimatedSprite::GetAnimations() const
{
	std::vector<std::string> result;
	for(auto iter = animations.begin(); iter != animations.end(); ++iter)
	{
		result.push_back(iter->first);
	}

	return result;
}

bool AnimatedSprite::AddAnimation(const Animation animation, const std::string & name)
{
	assert(name.size() > 0U);

	if(animations.find(name) != animations.end())
	{
		return false;
	}

	animations[name] = animation;
	return true;
}

void AnimatedSprite::ForceAddAnimation(const Animation animation, const std::string & name)
{
	assert(name.size() > 0U);

	animations[name] = animation;
}

bool AnimatedSprite::SetAnimation(const std::string & name)
{
	auto findresult = animations.find(name);
	if(findresult == animations.end())
	{
		return false;
	}

	currentAnimation = &(findresult->second);

	setTextureRect(sf::IntRect(
		currentAnimation->frameStart.x,
		currentAnimation->frameStart.y,
		currentAnimation->frameSize.x,
		currentAnimation->frameSize.y));
	currentFrame = 0U;
	currentFrameTime = 0U;

	return true;
}

bool AnimatedSprite::RemoveAnimation(const std::string & name)
{
	auto findresult = animations.find(name);
	if(findresult != animations.end())
	{
		if(currentAnimation == &(findresult->second))
		{
			currentAnimation = nullptr;
		}
		animations.erase(findresult);
		return true;
	}

	return false;
}

bool AnimatedSprite::IsAnimationFinished() const
{
	return currentFrame >= currentAnimation->frameCount;
}

void AnimatedSprite::FlipHorizontally()
{
	auto scale = getScale();
	scale.x *= -1.f;
	setScale(scale);
}

void AnimatedSprite::FlipVertically()
{
	auto scale = getScale();
	scale.y *= -1.f;
	setScale(scale);
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

void AnimatedSprite::Load(const std::string & animationFile, sf::Texture & textureStorage)
{
	auto lines = Platform::LoadTextFile(animationFile, true, true);

	for(size_t i = 0U; i < lines.size(); ++i)
	{
		std::stringstream ss;
		ss.str(lines[i]);

		std::string key;
		ss >> key;

		const auto header = GetHeader(key);
		switch(header)
		{
			case AnimationHeader::TextureSource:
			{
				std::string value;
				ss >> value;
				if(!textureStorage.loadFromFile(value))
				{
					throw std::runtime_error("Failed to load texture <" + value + "> specified in animation file <" + animationFile + ">.");
				}
				setTexture(textureStorage);
			}
			break;

			case AnimationHeader::Animation:
			{
				std::string value;
				ss >> value;

				++i;
				AddAnimation(LoadAnimation(lines, i), value);
				--i; // decrement once because next loop we should consider that position
			}
			break;

			default:
			break;
		}
	}
}

void AnimatedSprite::Update(const sf::Time & elapsed)
{
	if(currentAnimation == nullptr)
		return;

	currentFrameTime += elapsed.asMilliseconds();
	if(currentFrameTime >= currentAnimation->frameTime)
	{
		currentFrameTime = 0U;
		GetNextFrame();
	}
}

AnimatedSprite & AnimatedSprite::operator=(const AnimatedSprite & other)
{
	Sprite::operator=(other);
	animations = other.animations;
	currentAnimation = nullptr;
	currentFrame = other.currentFrame;
	currentFrameTime = other.currentFrameTime;

	if(other.currentAnimation != nullptr)
	{
		for(auto iter = other.animations.begin(); iter != other.animations.end(); ++iter)
		{
			if(&(iter->second) == other.currentAnimation)
			{
				SetAnimation(iter->first);
				break;
			}
		}
	}

	return *this;
}

AnimatedSprite::AnimatedSprite()
	: Sprite(),
	animations(),
	currentAnimation(nullptr),
	currentFrame(0U),
	currentFrameTime(0U)
{
}

AnimatedSprite::AnimatedSprite(const AnimatedSprite & other)
	: Sprite(other),
	animations(other.animations),
	currentAnimation(nullptr),
	currentFrame(other.currentFrame),
	currentFrameTime(other.currentFrameTime)
{
	if(other.currentAnimation != nullptr)
	{
		for(auto iter = other.animations.begin(); iter != other.animations.end(); ++iter)
		{
			if(&(iter->second) == other.currentAnimation)
			{
				SetAnimation(iter->first);
				break;
			}
		}
	}
}