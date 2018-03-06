#include "baseobstacle.hpp"

namespace Obstacle
{
	Type Base::GetType() const
	{
		return type;
	}

	const sf::FloatRect Base::GetKillBounds() const
	{
		return obstacleSprite.getGlobalBounds();
	}

	bool Base::IsUnharmful() const
	{
		return neutralized || sensorEnabled;
	}

	bool Base::IsActive() const
	{
		return !neutralized;
	}

	bool Base::IsNeutralizedByPlayer() const
	{
		return playerNeutralized;
	}

	void Base::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
	{
		SetPosition(sf::Vector2f(windowWidth, floorYcoord - obstacleSprite.getGlobalBounds().height));
	}

	const sf::Vector2f & Base::GetPosition() const
	{
		return obstacleSprite.getPosition();
	}

	const sf::Vector2f Base::GetObstacleCenter() const
	{
		const auto bounds = obstacleSprite.getGlobalBounds();
		return sf::Vector2f(bounds.left + (bounds.width / 2.f), bounds.top + (bounds.height / 2.f));
	}

	Base::Base(const Type & t, const bool playerHasSensor)
		: type(t),
		obstacleSprite(),
		neutralized(false),
		playerNeutralized(false),
		sensorEnabled(playerHasSensor)
	{
	}
}
