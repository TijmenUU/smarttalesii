#include "../../util/vectormath.hpp"
#include "../resourcecache.hpp"
#include "../soundmanager.hpp"
#include "doorobstacle.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-32, 450);
	const sf::Vector2f cLocalInteractionCenter(160, 380);
	const sf::Vector2f cLocalHintPosition(160, 150);
	const float cInteractionRadius = 200.f;

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
		auto & sfx = ResourceCache::GetInstance().GetSoundBuffer("door-open");
		SoundManager::GetInstance().PlaySFX(sfx);
	}

	bool Door::IsInteractionInBounds(const Inputhandler & input) const
	{
		const auto pos = input.PointingDeviceWorldPosition();
		return VectorMathF::Distance(pos, obstacleSprite.getPosition() + cLocalInteractionCenter) < cInteractionRadius;
	}

	bool Door::HandleInput(const Inputhandler & input)
	{
		const uint8_t gestureInfo = static_cast<uint8_t>(TrackGestures(input));
		if(gestureInfo & gestureFlag)
		{
			Neutralize();

			// TODO possibly fix this if necessary, would require custom animation
			if((gestureInfo & static_cast<uint8_t>(GestureType::Horizontal_LeftToRight)) && !sensorEnabled)
			{
				obstacleSprite.SetHorizontalFlip(true);
			}

			return true;
		}

		return false;
	}

	bool Door::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		if(playerBounds.left + playerBounds.width > sensorSprite.getPosition().x)
		{
			Neutralize();

			return true;
		}

		return false;
	}

	sf::Vector2f Door::GetHintPosition() const
	{
		return obstacleSprite.getPosition() + cLocalHintPosition;
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

	Base * Door::Clone() const
	{
		return new Door(*this);
	}

	Door::Door(bool playerHasSensor)
		: GestureSensorBase(ResourceCache::GetInstance().GetSpriteSheet("door"), 
			ResourceCache::GetInstance().GetSpriteSheet("active_ir"), 
			48, 
			50.f, 
			Type::Door, 
			playerHasSensor)
	{
		if(sensorEnabled)
		{
			obstacleSprite.SetAnimation("active-enhanced");
		}
	}
}
