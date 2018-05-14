/*
	phoneobstacle.hpp

	This class implements the phone obstacle and defines
	a whole bunch of variables for this in its cpp file
*/

#pragma once
#include "gestureobstacle.hpp"

namespace Obstacle
{
	class Phone : public GestureBase
	{
	private:
		float currentTimeout = 0.f;

	protected:
		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		bool IsInteractionInBounds(const Inputhandler & input) const override;

	public:
		void Neutralize() override;

		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		void SetPosition(const sf::Vector2f & p) override;
		void Move(const float x, const float y) override;
		void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord) override;

		UpdateResult Update(const sf::Time & elapsed,
			const Inputhandler & input,
			const float horizontalDisplacement,
			const sf::FloatRect & playerBounds) override;

		Base * Clone() const override;

		Phone(const bool playerHasSensor);
	};
}