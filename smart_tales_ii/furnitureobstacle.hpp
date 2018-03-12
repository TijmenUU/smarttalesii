#pragma once
#include "gesturesensorobstacle.hpp"

namespace Obstacle
{
	class Furniture : public GestureSensorBase
	{
	private:
	protected:
		bool IsInteractionInBounds(const Inputhandler & input) const override;

		void UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;

	public:
		sf::Vector2f GetScoreBubbleSpawnPosition() const override;
		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		virtual void SetPosition(const sf::Vector2f & p) override;
		virtual void Move(const float x, const float y) override;

		void Load(std::list<sf::Texture>& textureStorage) override;

		Base * Clone() const override;

		Furniture(const bool playerHasSensor);
	};
}
