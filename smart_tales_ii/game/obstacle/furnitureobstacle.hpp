/*
	furnitureobstacle.hpp

	This class implements the furniture obstacle and defines
	a whole bunch of variables for this in its cpp file
*/

#pragma once
#include "base/gesturesensorobstacle.hpp"

namespace Obstacle
{
	class Furniture : public GestureSensorBase
	{
	private:
		bool isFalling = false;
		sf::Vector2f fallVelocity = sf::Vector2f(0.f, 0.f);
		float angularVelocity = 0.f;

	protected:
		void Fall(const sf::Vector2f & force, const sf::Vector2f & forceOrigin);

		bool IsInteractionInBounds(const Inputhandler & input) const override;
		bool HandleInput(const Inputhandler & input) override;
		bool UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;

	public:
		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		virtual void SetPosition(const sf::Vector2f & p) override;
		virtual void Move(const float x, const float y) override;

		UpdateResult Update(const sf::Time & elapsed,
			const Inputhandler & input,
			const float horizontalDisplacement,
			const sf::FloatRect & playerBounds) override;

		Base * Clone() const override;

		Furniture(const bool playerHasSensor);
	};
}
