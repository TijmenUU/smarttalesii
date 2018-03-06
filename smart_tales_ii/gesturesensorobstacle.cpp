#include "gesturesensorobstacle.hpp"

namespace Obstacle
{
	void GestureSensorBase::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(obstacleSprite, states);
		if(sensorEnabled)
			target.draw(sensorSprite, states);
	}

	void GestureSensorBase::Neutralize()
	{
		obstacleSprite.SetAnimation("neutralized");
		if(sensorEnabled)
		{
			sensorSprite.SetAnimation("activated");
		}
		neutralized = true;
	}

	void GestureSensorBase::Update(const sf::Time & elapsed, 
		const Inputhandler & input, 
		const float horizontalDisplacement, 
		const sf::FloatRect & playerBounds)
	{
		if(!neutralized)
		{
			HandleInput(input);
			
			if(sensorEnabled)
				UpdateSensorTrigger(playerBounds);
		}

		obstacleSprite.Update(elapsed);
		sensorSprite.Update(elapsed);

		Move(horizontalDisplacement, 0.f);
	}

	GestureSensorBase::GestureSensorBase(const uint8_t & gestureFlag, 
		const float gestureMinWorldTravel, 
		const Type & t, 
		const bool playerHasSensor)
		: GestureBase(gestureFlag, gestureMinWorldTravel, t, playerHasSensor),
		sensorSprite()
	{
	}
}