#include "furnitureobstacle.hpp"

#include "vectormath.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-80, 73);
	const sf::Vector2f cLocalHintPosition(50, -40);

	bool Furniture::IsInteractionInBounds(const Inputhandler & input) const
	{
		return obstacleSprite.getGlobalBounds().contains(input.PointingDeviceWorldPosition());
	}

	void Furniture::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		if(playerBounds.intersects(sensorSprite.getGlobalBounds()))
		{
			Neutralize();
		}
	}

	sf::Vector2f Furniture::GetScoreBubbleSpawnPosition() const
	{
		return cLocalHintPosition + obstacleSprite.getPosition();
	}

	sf::Vector2f Furniture::GetHintPosition() const
	{
		return GetScoreBubbleSpawnPosition();
	}

	bool Furniture::CanDespawn() const
	{
		const auto bounds = sensorSprite.getGlobalBounds();
		return bounds.width + bounds.left < 0.f;
	}

	void Furniture::SetPosition(const sf::Vector2f & p)
	{
		obstacleSprite.setPosition(p);
		sensorSprite.setPosition(p + cLocalSensorPosition);
	}

	void Furniture::Move(const float x, const float y)
	{
		auto pos = obstacleSprite.getPosition();
		pos.x += x;
		pos.y += y;

		SetPosition(pos);
	}

	void Furniture::Load(std::list<sf::Texture>& textureStorage)
	{
		textureStorage.emplace_back();
		obstacleSprite.LoadFromFile("animation/furniture.txt", textureStorage.back());
		obstacleSprite.SetAnimation("active");

		textureStorage.emplace_back();
		sensorSprite.LoadFromFile("animation/livetile.txt", textureStorage.back());
		sensorSprite.SetAnimation("idle");
	}

	Base * Furniture::Clone() const
	{
		return new Furniture(*this);
	}

	Furniture::Furniture(const bool playerHasSensor)
		: GestureSensorBase(8, 50.f, Type::Furniture, playerHasSensor)
	{
	}
}