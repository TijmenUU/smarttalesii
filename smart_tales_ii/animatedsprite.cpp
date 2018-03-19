#include "animatedsprite.hpp"

#include <cassert>

namespace Animation
{
	void Sprite::UpdateTextureRect()
	{
		sf::IntRect textureRect = baseFrame;
		if(isFlippedHorizontally)
		{
			textureRect.left += textureRect.width;
			textureRect.width *= -1;
		}
		if(isFlippedVertically)
		{
			textureRect.top += textureRect.height;
			textureRect.height *= -1;
		}
		setTextureRect(textureRect);
	}

	void Sprite::GetFrame()
	{
		assert(currentAnimation != nullptr);
		
		if(currentAnimation->reverse)
		{
			baseFrame = sheet.GetFrame(*currentAnimation, currentAnimation->frameCount - (currentFrame + 1U));
		}
		else
		{
			baseFrame = sheet.GetFrame(*currentAnimation, currentFrame);
		}
		UpdateTextureRect();
	}

	bool Sprite::IsAnimationFinished() const
	{
		return currentFrame >= currentAnimation->frameCount;
	}

	void Sprite::FlipHorizontally()
	{
		isFlippedHorizontally = !isFlippedHorizontally;
	}

	void Sprite::FlipVertically()
	{
		isFlippedVertically = !isFlippedVertically;
	}

	bool Sprite::SetAnimation(const std::string & name)
	{
		auto * candidate = sheet.GetAnimation(name);
		if(candidate != nullptr)
		{
			currentFrameTime = 0U;
			currentFrame = 0U;
			currentAnimation = candidate;
			GetFrame();
			return true;
		}

		return false;
	}

	void Sprite::Update(const sf::Time & elapsed)
	{
		assert(currentAnimation != nullptr);

		if(IsAnimationFinished())
		{
			return;
		}

		currentFrameTime += elapsed.asMilliseconds();
		if(currentFrameTime < currentAnimation->frameTime)
		{
			return;
		}

		currentFrameTime = 0U;
		++currentFrame;
		if(currentFrame < currentAnimation->frameCount)
		{
			GetFrame();
		}
		else if(currentAnimation->loop)
		{
			currentFrame = 0U;
			GetFrame();
		}
		else
		{
			currentFrame = currentAnimation->frameCount;
		}
	}

	Sprite::Sprite(const Sheet & sheetRef)
		: sf::Sprite(sheetRef.GetTexture()),
		sheet(sheetRef),
		currentAnimation(nullptr),
		baseFrame(),
		currentFrame(0U),
		currentFrameTime(0U),
		isFlippedHorizontally(false),
		isFlippedVertically(false)
	{
	}
}
