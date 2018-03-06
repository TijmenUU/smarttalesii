#pragma once
#include "inputhandler.hpp"
#include "obstacletype.hpp"

#include <SFML\Graphics.hpp>
#include <vector>

namespace Obstacle
{
	class Base : public sf::Drawable
	{
	private:
	protected:
		Type type;
		AnimatedSprite obstacleSprite;
		bool neutralized, playerNeutralized;
		bool sensorEnabled;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
		virtual void Neutralize() = 0;

	public:
		Type GetType() const;
		virtual const sf::FloatRect GetKillBounds() const;
		virtual const sf::Vector2f & GetPosition() const;
		virtual const sf::Vector2f GetObstacleCenter() const;
		virtual const sf::Vector2f GetScoreBubbleSpawnPosition() const = 0;
		virtual const sf::Vector2f GetHintPosition() const = 0;

		virtual bool IsUnharmful() const;
		virtual bool IsActive() const;
		virtual bool IsNeutralizedByPlayer() const;
		virtual bool CanDespawn() const = 0;

		virtual void SetPosition(const sf::Vector2f & p) = 0;
		virtual void Move(const float x, const float y) = 0;
		virtual void SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord);

		virtual void Load(std::list<sf::Texture> & textureStorage) = 0;
		virtual void Update(const sf::Time & elapsed,
			const Inputhandler & input,
			const float horizontalDisplacement,
			const sf::FloatRect & playerBounds) = 0;

		virtual Base * Clone() const = 0;

		Base(const Type & t, const bool playerHasSensor);
		virtual ~Base() = default;
	};

	
}
