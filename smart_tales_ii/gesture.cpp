#include "gesture.hpp"
#include "vectormath.hpp"

#include <array>
#include <cmath>
#include <utility>

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

bool SwipeGesture::IsInProgress() const
{
	return gestureInProgress;
}

void SwipeGesture::SetPosition(const sf::Vector2f & newPos)
{
	position = newPos;
}

sf::Vector2f SwipeGesture::GetPosition() const
{
	return position;
}

void SwipeGesture::SetInteractionRadius(const float newRadius)
{
	radius = newRadius;
}

float SwipeGesture::GetInteractionRadius() const
{
	return radius;
}

SwipeType SwipeGesture::Update(const Inputhandler & input)
{
	// TODO add configurable button
	if(!gestureInProgress && input.PointingDeviceIsDown())
	{
		const auto inputpos = input.PointingDeviceWorldPosition();
		const float distance = VectorMathF::Distance(inputpos, position);

		if(distance < radius)
		{
			gestureInProgress = true;
			startWindowPosition = input.PointingDeviceWindowPosition();
		}
	}
	else if(input.PointingDeviceReleasedEvent() && gestureInProgress)
	{
		gestureInProgress = false;

		const auto endWindowPosition = input.PointingDeviceWindowPosition();
		const float distance = VectorMathI::Distance(startWindowPosition, endWindowPosition);
		if(distance < minDist)
		{
			return SwipeType::Tap;
		}

		const auto difference = endWindowPosition - startWindowPosition;
		if(std::abs(difference.x) > std::abs(difference.y))
		{
			if(difference.x > 0.f)
			{
				return SwipeType::Horizontal_LeftToRight;
			}
			else
			{
				return SwipeType::Horizontal_RightToLeft;
			}
		}
		else
		{
			if(difference.y > 0.f)
			{
				return SwipeType::Vertical_Downwards;
			}
			else
			{
				return SwipeType::Vertical_Upwards;
			}
		}
	}

	if(gestureInProgress)
	{
		return SwipeType::InProgress;
	}
	else
	{
		return SwipeType::None;
	}
}

void SwipeGesture::Reset()
{
	gestureInProgress = false;
}

SwipeGesture::SwipeGesture(const float interactionRadius,
	const sf::Vector2f & spawnPos, 
	const float minimumDistance)
	: position(spawnPos),
	radius(interactionRadius),
	minDist(minimumDistance),
	gestureInProgress(false),
	startWindowPosition(0.f, 0.f)
{
}
