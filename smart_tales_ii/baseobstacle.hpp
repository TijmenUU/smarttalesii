#pragma once
#include "animatedsprite.hpp"
#include "inputhandler.hpp"
#include "obstacletype.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

namespace Obstacle
{
	class Base : public sf::Drawable
	{
	private:
	protected:
		Type type;
		Animation::Sprite obstacleSprite;
		bool neutralized = false;
		bool playerNeutralized = false;
		bool sensorEnabled;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
		virtual void Neutralize() = 0;

	public:
		Type GetType() const;
		virtual sf::FloatRect GetKillBounds() const;
		virtual const sf::Vector2f & GetPosition() const;
		virtual sf::Vector2f GetObstacleCenter() const;
		virtual sf::Vector2f GetNeutralizationPosition() const;
		virtual sf::Vector2f GetHintPosition() const = 0;

		virtual bool IsUnharmful() const;
		virtual bool IsActive() const;
		virtual bool IsNeutralizedByPlayer() const;
		virtual bool CanDespawn() const = 0;

		virtual void SetPosition(const sf::Vector2f & p) = 0;
		virtual void Move(const float x, const float y) = 0;
		virtual void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord);

		virtual void Update(const sf::Time & elapsed,
			const Inputhandler & input,
			const float horizontalDisplacement,
			const sf::FloatRect & playerBounds) = 0;

		virtual Base * Clone() const = 0;

		Base(Type t, const Animation::Sheet & obstacleSheet, const bool playerHasSensor);
		virtual ~Base() = default;
	};

	
}
