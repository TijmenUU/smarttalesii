#pragma once
#include "animationsheet.hpp"

namespace Animation
{
	class Sprite : public sf::Sprite
	{
	private:
		const Sheet & sheet;
		
		const Animation * currentAnimation;
		sf::IntRect baseFrame;
		unsigned int currentFrame;
		unsigned int currentFrameTime;
		bool isFlippedHorizontally;
		bool isFlippedVertically;

		void UpdateTextureRect();
		void GetFrame();

	public:
		virtual bool IsAnimationFinished() const;

		virtual void FlipHorizontally();
		virtual void FlipVertically();
		
		bool SetAnimation(const std::string & name);

		virtual void Update(const sf::Time & elapsed);

		// Remember to set the animation afterwards!
		Sprite(const Sheet & sheetRef);
	};
}
