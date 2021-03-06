/*
	animatedsprite.hpp

	An extended sf::Sprite class that uses the SpriteSheet class.
	It animates the texture coordinates of the sprite accordingly.

	After construction the Sprite still needs the animation to be
	set. If it isn't set it is invisble.
*/

#pragma once
#include "animationsheet.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

namespace Animation
{
	class Sprite : public sf::Sprite
	{
	private:
		const Sheet & sheet;
		
		const Animation * currentAnimation = nullptr;
		sf::IntRect baseFrame;
		unsigned int currentFrame = 0U;
		unsigned int currentFrameTime = 0U;
		bool isFlippedHorizontally = false;
		bool isFlippedVertically = false;

		void UpdateTextureRect();
		void GetFrame();

	public:
		virtual bool IsAnimationFinished() const;

		// This flip call is not free, so be careful with lots
		// of repeated calls to this function
		virtual void SetHorizontalFlip(const bool v);
		// This flip call is not free, so be careful with lots
		// of repeated calls to this function
		virtual void SetVerticalFlip(const bool v);
		bool IsFlippedHorizontally() const;
		bool IsFlippedVertically() const;
		
		bool SetAnimation(const std::string & name);

		virtual void Update(const sf::Time & elapsed);
		virtual void Update(const Sprite & parent);

		// Remember to set the animation afterwards!
		Sprite(const Sheet & sheetRef);
	};
}
