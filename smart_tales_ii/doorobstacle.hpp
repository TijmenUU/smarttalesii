/*
	doorobstacle.hpp

	This class implements the door obstacle and defines
	a whole bunch of variables for this in its cpp file
*/

#pragma once
#include "gesturesensorobstacle.hpp"

namespace Obstacle
{
	class Door : public GestureSensorBase
	{
	private:
	protected:
		void Neutralize() override;

		bool IsInteractionInBounds(const Inputhandler & input) const override;
		bool HandleInput(const Inputhandler & input) override;

		bool UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;

	public:
		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		void SetPosition(const sf::Vector2f & p) override;
		void Move(const float x, const float y) override;

		Base * Clone() const override;

		Door(bool playerHasSensor);
	};
}
