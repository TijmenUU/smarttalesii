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
		
		virtual void UpdateSensorTrigger(const sf::FloatRect & playerBounds) = 0;

	public:
		void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord) override;

		void Update(const sf::Time & elapsed,
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
