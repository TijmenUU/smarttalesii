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
		void HandleInput(const Inputhandler & input) override;

		void UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;

	public:
		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		void SetPosition(const sf::Vector2f & p) override;
		void Move(const float x, const float y) override;

		Base * Clone() const override;

		Door(bool playerHasSensor);
	};
}
