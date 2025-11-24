#include "baseobstacle.hpp"

namespace Obstacle
{
    Type Base::GetType() const { return type; }

    sf::FloatRect Base::GetKillBounds() const { return obstacleSprite.getGlobalBounds(); }

    bool Base::IsUnharmful() const { return neutralized || sensorEnabled; }

    bool Base::IsActive() const { return !neutralized; }

    void Base::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
    {
        SetPosition(sf::Vector2f(windowWidth, floorYcoord - obstacleSprite.getGlobalBounds().size.y));
    }

    const sf::Vector2f Base::GetPosition() const { return obstacleSprite.getPosition(); }

    sf::Vector2f Base::GetObstacleCenter() const
    {
        const auto bounds = obstacleSprite.getGlobalBounds();
        return sf::Vector2f(bounds.position.x + (bounds.size.x / 2.f), bounds.position.y + (bounds.size.y / 2.f));
    }

    sf::Vector2f Base::GetNeutralizationPosition() const { return GetObstacleCenter(); }

    Base::Base(Type t, const Animation::Sheet & obstacleSheet, const bool playerHasSensor)
     : type(t), obstacleSprite(obstacleSheet), sensorEnabled(playerHasSensor)
    {
        obstacleSprite.SetAnimation("active");
    }
}
