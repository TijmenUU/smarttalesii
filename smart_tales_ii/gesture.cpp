#include "gesture.hpp"
#include "vectormath.hpp"

#include <cmath>
//#include <iomanip>
//#include <sstream>

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

// debug
//std::string ToString(const sf::Vector2f & vec)
//{
//	std::stringstream ss;
//	ss << std::fixed << std::setprecision(2);
//	ss << 'X' << vec.x << " Y" << vec.y;
//
//	return ss.str();
//}

SwipeType SwipeGesture::Update(const Inputhandler & input)
{
	// TODO add configurable button
	if(!gestureInProgress && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		const auto mousePos = input.GetMouseWorldCoordinate();
		const float distance = VectorMathF::Distance(mousePos, position);

		if(distance < radius)
		{
			gestureInProgress = true;
			start = input.GetMouseWindowCoordinate();
		}
	}
	else if(input.WasButtonReleased(sf::Mouse::Button::Left) && gestureInProgress)
	{
		gestureInProgress = false;

		const auto mousePos = input.GetMouseWindowCoordinate();
		const float distance = VectorMathI::Distance(start, mousePos);
		if(distance < minDist)
		{
			return SwipeType::Tap;
		}

		const auto difference = mousePos - start;
		//printf("Start %s End %s Difference %s \n", ToString(start).c_str(), ToString(mousePos).c_str(), ToString(difference).c_str()); // debug
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
	start(0.f, 0.f)
{
}
