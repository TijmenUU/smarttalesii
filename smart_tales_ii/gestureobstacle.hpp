#pragma once
#include "baseobstacle.hpp"

namespace Obstacle
{
	enum class GestureType : uint8_t
	{
		None = 0,
		InProgress = 1,
		Tap = 2,
		Vertical_Upwards = 4,
		Vertical_Downwards = 8,
		Horizontal_LeftToRight = 16,
		Horizontal_RightToLeft = 32
	};

	class GestureBase : public Base
	{
	private:
		bool gestureInProgress;
		sf::Vector2f gestureStart;
		float gestureMinDistance;

	protected:
		uint8_t gestureFlag;

		virtual bool IsInteractionInBounds(const Inputhandler & input) const = 0;
		virtual GestureType TrackGestures(const Inputhandler & input);
		virtual void HandleInput(const Inputhandler & input);

	public:
		GestureBase(const uint8_t & gestureFlag, 
			const float gestureMinWorldTravel, 
			const Type & t, 
			const bool playerHasSensor);
	};
}

