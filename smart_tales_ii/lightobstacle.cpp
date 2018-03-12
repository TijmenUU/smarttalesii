#include "lightobstacle.hpp"

#include "alignmenthelp.hpp"
#include "vectormath.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-100, 200);
	const sf::Vector2f cLocalSwitchPosition(-100, 250);
	const float cInteractionRadius = 50.f;

	bool Light::IsInteractionInBounds(const Inputhandler & input) const
	{
		const auto center = Alignment::GetRectangleCenter(lightSwitch.getGlobalBounds());
		const auto distance = VectorMathF::Distance(center, input.PointingDeviceWorldPosition());
		return distance < cInteractionRadius;
	}

	void Light::HandleInput(const Inputhandler & input)
	{
		if(input.PointingDeviceReleasedEvent() && IsInteractionInBounds(input))
		{
			playerNeutralized = true;
			Neutralize();
			lightSwitch.SetAnimation("activated");
		}
	}

	void Light::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
	{
		SetPosition(sf::Vector2f(windowWidth - cLocalSwitchPosition.x, 0.f));
	}

	void Light::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		if(playerBounds.left + playerBounds.width > sensorSprite.getPosition().x)
		{
			Neutralize();
			lightSwitch.SetAnimation("activated");
		}
	}

	void Light::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(lightSwitch, states);
		if(sensorEnabled)
			target.draw(sensorSprite);
		target.draw(obstacleSprite, states);
	}

	sf::Vector2f Light::GetNeutralizationPosition() const
	{
		return Alignment::GetRectangleCenter(lightSwitch.getGlobalBounds());
	}

	sf::Vector2f Light::GetScoreBubbleSpawnPosition() const
	{
		return lightSwitch.getPosition();
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
		lightSwitch.setPosition(p + cLocalSwitchPosition);
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

		textureStorage.emplace_back();
		lightSwitch.LoadFromFile("animation/lightswitch.txt", textureStorage.back());
		lightSwitch.SetAnimation("idle");
	}

	Base * Light::Clone() const
	{
		return new Light(*this);
	}

	Light::Light(const bool playerHasSensor)
		: GestureSensorBase(2U, 50.f, Type::Light, playerHasSensor)
	{
	}
}