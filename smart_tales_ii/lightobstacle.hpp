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
		bool IsInteractionInBounds(const Inputhandler & input) const override;
		void HandleInput(const Inputhandler & input) override;
		void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord) override;

		void UpdateSensorTrigger(const sf::FloatRect & playerBounds) override;
		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	public:
		sf::Vector2f GetNeutralizationPosition() const override;
		sf::Vector2f GetScoreBubbleSpawnPosition() const override;
		sf::Vector2f GetHintPosition() const override;

		bool CanDespawn() const override;

		void SetPosition(const sf::Vector2f & p) override;
		void Move(const float x, const float y) override;

		Base * Clone() const override;

		Light(const Animation::Sheet & lightSwitchSheet,
			sf::Texture & storage,
			const Animation::Sheet & obstacleSheet,
			const Animation::Sheet & sensorSheet, 
			const bool playerHasSensor);
	};
}
