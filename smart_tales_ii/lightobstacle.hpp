#pragma once
#include "gesturesensorobstacle.hpp"

namespace Obstacle
{
	class Light : public GestureSensorBase
	{
	private:
		sf::Sprite sensorBeam;
		bool showBeam;
		Animation::Sprite lightSwitch;

	protected:
		void Neutralize() override;
		bool IsInteractionInBounds(const Inputhandler & input) const override;
		bool HandleInput(const Inputhandler & input) override;
		void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord) override;

		bool UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;
		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	public:
		sf::Vector2f GetNeutralizationPosition() const override;
		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		void SetPosition(const sf::Vector2f & p) override;
		void Move(const float x, const float y) override;

		Base * Clone() const override;

		Light(const bool playerHasSensor);
	};
}
