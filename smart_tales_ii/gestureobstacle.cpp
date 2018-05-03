#include "gestureobstacle.hpp"

#include "vectormath.hpp"

namespace Obstacle
{
	GestureType GestureBase::TrackGestures(const Inputhandler & input)
	{
		if(input.PointingDevicePressedEvent() && IsInteractionInBounds(input))
		{
			gestureInProgress = true;
			gestureStart = input.PointingDeviceWorldPosition();
		}	
		else if(input.PointingDeviceReleasedEvent() && gestureInProgress)
		{
			gestureInProgress = false;

			const auto endPos = input.PointingDeviceWorldPosition();
			const float distanceTravelled = VectorMathF::Distance(gestureStart, endPos);
			if(distanceTravelled <= gestureMinDistance)
			{
				return GestureType::Tap;
			}
			else
			{
				// We don't care about accurate distance, just which one is further
				const auto ydistance = endPos.y - gestureStart.y;
				const auto xdistance = endPos.x - gestureStart.x;
				if(std::abs(ydistance) > std::abs(xdistance))
				{
					if(ydistance < 0.f)
					{
						return GestureType::Vertical_Upwards;
					}

					return GestureType::Vertical_Downwards;
				}
				else
				{
					if(xdistance < 0.f)
					{
						return GestureType::Horizontal_RightToLeft;
					}

					return GestureType::Horizontal_LeftToRight;
				}
			}
		}

		return GestureType::None;
	}

	bool GestureBase::HandleInput(const Inputhandler & input)
	{
		const uint8_t gestureInfo = static_cast<uint8_t>(TrackGestures(input));
		if(gestureInfo & gestureFlag)
		{
			Neutralize();
			return true;
		}

		return false;
	}

	GestureBase::GestureBase(const uint8_t _gestureFlag,
		const float gestureMinWorldTravel, 
		const Type t,
		const Animation::Sheet & obstacleSheet,
		const bool playerHasSensor)
		: Base(t, obstacleSheet, playerHasSensor),
		gestureMinDistance(gestureMinWorldTravel),
		gestureFlag(_gestureFlag)
	{
	}
}
