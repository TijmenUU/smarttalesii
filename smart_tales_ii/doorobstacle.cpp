#include "doorobstacle.hpp"

#include "vectormath.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-32, 450);
	const sf::Vector2f cLocalInteractionCenter(160, 380);
	const sf::Vector2f cLocalHintPosition(160, 150);
	const float cInteractionRadius = 200.f;
	const float cSensorTriggerDistance = 50.f;

	void Door::Neutralize()
	{
		if(sensorEnabled)
		{
			sensorSprite.SetAnimation("activated");
			obstacleSprite.SetAnimation("neutralized-enhanced");
		}
		else
		{
			obstacleSprite.SetAnimation("neutralized");
		}
		neutralized = true;
	}

	bool Door::IsInteractionInBounds(const Inputhandler & input) const
	{
		const auto pos = input.PointingDeviceWorldPosition();
		return VectorMathF::Distance(pos, obstacleSprite.getPosition() + cLocalInteractionCenter) < cInteractionRadius;
	}

	void Door::HandleInput(const Inputhandler & input)
	{
		const uint8_t gestureInfo = static_cast<uint8_t>(TrackGestures(input));
		if(gestureInfo & gestureFlag)
		{
			playerNeutralized = true;
			Neutralize();

			// TODO possibly fix this if necessary, would require custom animation
			if((gestureInfo & static_cast<uint8_t>(GestureType::Horizontal_LeftToRight)) && !sensorEnabled)
			{
				obstacleSprite.FlipHorizontally();
			}
		}
	}

	void Door::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		if(playerBounds.left + playerBounds.width > sensorSprite.getPosition().x)
		{
			Neutralize();
		}
	}

	sf::Vector2f Door::GetScoreBubbleSpawnPosition() const
	{
		return cLocalHintPosition + obstacleSprite.getPosition();
	}

	sf::Vector2f Door::GetHintPosition() const
	{
		return GetScoreBubbleSpawnPosition();
	}

	bool Door::CanDespawn() const
	{
		const auto bounds = obstacleSprite.getGlobalBounds();
		return bounds.width + bounds.left < 0.f;
	}

	void Door::SetPosition(const sf::Vector2f & p)
	{
		obstacleSprite.setPosition(p);
		sensorSprite.setPosition(p + cLocalSensorPosition);
	}

	void Door::Move(const float x, const float y)
	{
		auto pos = obstacleSprite.getPosition();
		pos.x += x;
		pos.y += y;

		SetPosition(pos);
	}

	void Door::Load(std::list<sf::Texture>& textureStorage)
	{
		textureStorage.emplace_back();
		obstacleSprite.LoadFromFile("animation/door.txt", textureStorage.back());
		if(sensorEnabled)
		{
			obstacleSprite.SetAnimation("active-enhanced");
		}
		else
		{
			obstacleSprite.SetAnimation("active");
		}

		textureStorage.emplace_back();
		sensorSprite.LoadFromFile("animation/active_ir.txt", textureStorage.back());
		sensorSprite.SetAnimation("idle");
	}

	Base * Door::Clone() const
	{
		return new Door(*this);
	}

	Door::Door(const bool playerHasSensor)
		: GestureSensorBase(48, 50.f, Type::Door, playerHasSensor)
	{
	}
}
