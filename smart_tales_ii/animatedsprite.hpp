#pragma once
#include "animationsheet.hpp"

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

		virtual void FlipHorizontally();
		virtual void FlipVertically();
		
		bool SetAnimation(const std::string & name);

		virtual void Update(const sf::Time & elapsed);
		virtual void Update(const Sprite & parent);

		// Remember to set the animation afterwards!
		Sprite(const Sheet & sheetRef);
	};
}
