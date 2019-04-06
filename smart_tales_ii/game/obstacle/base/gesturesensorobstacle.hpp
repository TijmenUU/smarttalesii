/*
	gesturesensorobstacle.hpp

	Base obstacle for 3 of the 4 obstacles in the game. Defines
	an obstacle that can be neutralized by gesture and has a
	sensor sprite in the game world.

	All obstacles except the phone derrive from this class.

	This class is virtual.
*/

#pragma once
#include "baseobstacle.hpp"
#include "gestureobstacle.hpp"

namespace Obstacle
{
	class GestureSensorBase : public GestureBase
	{
	protected:
		Animation::Sprite sensorSprite;

		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		void Neutralize() override;

		// Returns whether the sensor triggered
		virtual bool UpdateSensorTrigger(const sf::FloatRect & playerBounds) = 0;

	public:
		void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord) override;

		UpdateResult Update(const sf::Time & elapsed,
			const Inputhandler & input,
			const float horizontalDisplacement,
			const sf::FloatRect & playerBounds) override;

		GestureSensorBase(const Animation::Sheet & obstacleSheet,
			const Animation::Sheet & sensorSheet,
			const uint8_t gestureFlag,
			const float gestureMinWorldTravel,
			const Type t,
			const bool playerHasSensor);
	};
}
