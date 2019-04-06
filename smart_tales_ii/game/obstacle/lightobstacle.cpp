#include "../../util/alignmenthelp.hpp"
#include "../../util/vectormath.hpp"
#include "../resourcecache.hpp"
#include "../soundmanager.hpp"
#include "lightobstacle.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-100, 196);
	const sf::Vector2f cLocalSensorBeamPosition(cLocalSensorPosition + sf::Vector2f(-368, 14));
	const sf::Vector2f cLocalSwitchPosition(-100, 250);
	const float cInteractionRadius = 50.f;

	void Light::Neutralize()
	{
		GestureSensorBase::Neutralize();
		lightSwitch.SetAnimation("activated");
		auto & sfx = ResourceCache::GetInstance().GetSoundBuffer("switch");
		SoundManager::GetInstance().PlaySFX(sfx);
		showBeam = false;
	}

	bool Light::IsInteractionInBounds(const Inputhandler & input) const
	{
		const auto center = Alignment::GetRectangleCenter(lightSwitch.getGlobalBounds());
		const auto distance = VectorMathF::Distance(center, input.PointingDeviceWorldPosition());
		return distance < cInteractionRadius;
	}

	bool Light::HandleInput(const Inputhandler & input)
	{
		if(input.PointingDeviceReleasedEvent() && IsInteractionInBounds(input))
		{
			Neutralize();

			return true;
		}

		return false;
	}

	void Light::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
	{
		SetPosition(sf::Vector2f(windowWidth - cLocalSensorBeamPosition.x, 0.f));
	}

	bool Light::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		const auto bounds = sensorBeam.getGlobalBounds();
		if(playerBounds.left + playerBounds.width > (bounds.left + bounds.width / 2.f))
		{
			Neutralize();
			lightSwitch.SetAnimation("activated");
			showBeam = false;

			return true;
		}

		return false;
	}

	void Light::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(lightSwitch, states);
		if(sensorEnabled)
		{
			target.draw(sensorSprite, states);
			if(showBeam)
				target.draw(sensorBeam, states);
		}
		target.draw(obstacleSprite, states);
	}

	sf::Vector2f Light::GetNeutralizationPosition() const
	{
		return Alignment::GetRectangleCenter(lightSwitch.getGlobalBounds());
	}

	sf::Vector2f Light::GetHintPosition() const
	{
		const auto bounds = lightSwitch.getGlobalBounds();
		auto pos = Alignment::GetRectangleCenter(bounds);
		pos.y -= bounds.height;
		return pos;
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
		sensorBeam.setPosition(p + cLocalSensorBeamPosition);
		lightSwitch.setPosition(p + cLocalSwitchPosition);
	}

	void Light::Move(const float x, const float y)
	{
		auto pos = obstacleSprite.getPosition();
		pos.x += x;
		pos.y += y;

		SetPosition(pos);
	}

	Base * Light::Clone() const
	{
		return new Light(*this);
	}

	Light::Light(const bool playerHasSensor)
		: GestureSensorBase(ResourceCache::GetInstance().GetSpriteSheet("light"),
			ResourceCache::GetInstance().GetSpriteSheet("passive_ir"),
			2U,
			50.f,
			Type::Light,
			playerHasSensor),
		sensorBeam(ResourceCache::GetInstance().GetTexture("passive_ir_beam")),
		showBeam(playerHasSensor),
		lightSwitch(ResourceCache::GetInstance().GetSpriteSheet("lightswitch"))
	{
		lightSwitch.SetAnimation("idle");
	}
}
