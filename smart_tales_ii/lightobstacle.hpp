#pragma once
#include "gesturesensorobstacle.hpp"

namespace Obstacle
{
	class Light : public GestureSensorBase
	{
	private:
	protected:
		bool IsInteractionInBounds(const Inputhandler & input) const override;
		void HandleInput(const Inputhandler & input) override;
		void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord) override;

		void UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;

	public:
		const sf::Vector2f GetScoreBubbleSpawnPosition() const override;
		const sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		void SetPosition(const sf::Vector2f & p) override;
		void Move(const float x, const float y) override;

		void Load(std::list<sf::Texture>& textureStorage) override;

		Base * Clone() const override;

		Light(const bool playerHasSensor);
	};
}
