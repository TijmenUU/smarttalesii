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

	void GestureSensorBase::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
	{
		const auto offset = obstacleSprite.getPosition() - sensorSprite.getPosition();
		SetPosition(sf::Vector2f(windowWidth + offset.x, floorYcoord - obstacleSprite.getGlobalBounds().height));
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

	GestureSensorBase::GestureSensorBase(const Animation::Sheet & obstacleSheet,
		const Animation::Sheet & sensorSheet,
		const uint8_t gestureFlag,
		const float gestureMinWorldTravel,
		const Type t,
		const bool playerHasSensor)
		: GestureBase(gestureFlag, gestureMinWorldTravel, t, obstacleSheet, playerHasSensor),
		sensorSprite(sensorSheet)
	{
		sensorSprite.SetAnimation("idle");
	}
}
