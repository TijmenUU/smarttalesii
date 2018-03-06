#include "lightobstacle.hpp"

#include "vectormath.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-80, 200);
	const sf::Vector2f cLocalHintPosition(150, 100);

	bool Light::IsInteractionInBounds(const Inputhandler & input) const
	{
		return obstacleSprite.getGlobalBounds().contains(input.PointingDeviceWorldPosition());
	}

	void Light::HandleInput(const Inputhandler & input)
	{
		if(input.PointingDeviceReleasedEvent() && IsInteractionInBounds(input))
		{
			playerNeutralized = true;
			Neutralize();
		}
	}

	void Light::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
	{
		SetPosition(sf::Vector2f(windowWidth, 0.f));
	}

	void Light::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		if(playerBounds.left + playerBounds.width > sensorSprite.getPosition().x)
		{
			Neutralize();
		}
	}

	const sf::Vector2f Light::GetScoreBubbleSpawnPosition() const
	{
		return cLocalHintPosition + obstacleSprite.getPosition();
	}

	const sf::Vector2f Light::GetHintPosition() const
	{
		return GetScoreBubbleSpawnPosition();
	}

	bool Light::CanDespawn() const
	{
		const auto bounds = obstacleSprite.getGlobalBounds();
		return bounds.width + bounds.left < 0.f;
	}

	void Light::SetPosition(const sf::Vector2f & p)
	{
		obstacleSprite.setPosition(p);
		sensorSprite.setPosition(p + cLocalSensorPosition);
	}

	void Light::Move(const float x, const float y)
	{
		auto pos = obstacleSprite.getPosition();
		pos.x += x;
		pos.y += y;

		SetPosition(pos);
	}

	void Light::Load(std::list<sf::Texture>& textureStorage)
	{
		textureStorage.emplace_back();
		obstacleSprite.LoadFromFile("animation/light.txt", textureStorage.back());
		obstacleSprite.SetAnimation("active");

		textureStorage.emplace_back();
		sensorSprite.LoadFromFile("animation/passive_ir.txt", textureStorage.back());
		sensorSprite.SetAnimation("idle");
	}

	Base * Light::Clone() const
	{
		return new Light(*this);
	}

	Light::Light(const bool playerHasSensor)
		: GestureSensorBase(2, 25.f, Type::Light, playerHasSensor)
	{
	}
}