#include "furnitureobstacle.hpp"

#include "alignmenthelp.hpp"
#include "vectormath.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalSensorPosition(-80, 73);
	const sf::Vector2f cLocalHintPosition(50, -40);
	const float cFallingForce = 10.f;
	const float cFallingGravity = 5.f;

	void Furniture::Fall(const sf::Vector2f & force, const sf::Vector2f & forceOrigin)
	{
		isFalling = true;

		if(forceOrigin.x < Alignment::GetRectangleCenter(obstacleSprite.getGlobalBounds()).x)
		{
			angularVelocity = -3.f;
		}
		else
		{
			angularVelocity = 3.f;
		}
		
		fallVelocity = VectorMathF::SetLength(force, cFallingForce) + sf::Vector2f(0, cFallingGravity);
	}

	bool Furniture::IsInteractionInBounds(const Inputhandler & input) const
	{
		return obstacleSprite.getGlobalBounds().contains(input.PointingDeviceWorldPosition());
	}

	void Furniture::HandleInput(const Inputhandler & input)
	{
		const uint8_t gestureInfo = static_cast<uint8_t>(TrackGestures(input));
		if(gestureInfo & gestureFlag)
		{
			playerNeutralized = true;
			Neutralize();
			const auto mousepos = input.PointingDeviceWorldPosition();
			Fall(mousepos - gestureStart, mousepos);
		}
	}

	void Furniture::UpdateSensorTrigger(const sf::FloatRect & playerBounds)
	{
		if(playerBounds.intersects(sensorSprite.getGlobalBounds()))
		{
			Neutralize();
			Fall(sf::Vector2f(0, 1), sf::Vector2f(0, 0));
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
		const auto bounds = obstacleSprite.getGlobalBounds();
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

	void Furniture::Update(const sf::Time & elapsed, const Inputhandler & input, const float horizontalDisplacement, const sf::FloatRect & playerBounds)
	{
		if(isFalling)
		{
			obstacleSprite.move(fallVelocity.x + horizontalDisplacement, fallVelocity.y);
			obstacleSprite.rotate(angularVelocity);

			sensorSprite.move(horizontalDisplacement, 0.f);
		}
		else
		{
			GestureSensorBase::Update(elapsed, input, horizontalDisplacement, playerBounds);
		}
	}

	Base * Furniture::Clone() const
	{
		return new Furniture(*this);
	}

	Furniture::Furniture(const Animation::Sheet & obstacleSheet,
		const Animation::Sheet & sensorSheet, 
		const bool playerHasSensor)
		: GestureSensorBase(obstacleSheet, sensorSheet, 8, 50.f, Type::Furniture, playerHasSensor),
		isFalling(false),
		fallVelocity(0, 0),
		angularVelocity(0.f)
	{
	}
}