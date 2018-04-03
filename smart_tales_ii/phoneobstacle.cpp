#include "phoneobstacle.hpp"

#include "resourcecache.hpp"
#include "soundmanager.hpp"

namespace Obstacle
{
	const sf::Vector2f cLocalHintPosition(45, -30);
	const float cSpawnHeight = 135.f; // pixels

	void Phone::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(obstacleSprite, states);
	}

	void Phone::Neutralize()
	{
		neutralized = true;
		obstacleSprite.SetAnimation("neutralized");
		auto & sfx = ResourceCache::GetInstance().GetSoundBuffer("phone-pickup");
		SoundManager::GetInstance().PlaySFX(sfx);
	}

	bool Phone::IsInteractionInBounds(const Inputhandler & input) const
	{
		return obstacleSprite.getGlobalBounds().contains(input.PointingDeviceWorldPosition());
	}

	sf::Vector2f Phone::GetHintPosition() const
	{
		return cLocalHintPosition + obstacleSprite.getPosition();
	}

	bool Phone::CanDespawn() const
	{
		const auto bounds = obstacleSprite.getGlobalBounds();
		return bounds.width + bounds.left < 0.f;
	}

	void Phone::SetPosition(const sf::Vector2f & p)
	{
		obstacleSprite.setPosition(p);
	}

	void Phone::Move(const float x, const float y)
	{
		obstacleSprite.move(x, y);
	}

	void Phone::SetSpawnPosition(const unsigned int windowWidth, const float floorYcoord)
	{
#pragma warning(suppress: 4244) // Int to float is safe, resolution will not exceed float precision
		SetPosition(sf::Vector2f(windowWidth, floorYcoord - (cSpawnHeight + obstacleSprite.getGlobalBounds().width)));
	}

	void Phone::Update(const sf::Time & elapsed, const Inputhandler & input, const float horizontalDisplacement, const sf::FloatRect & playerBounds)
	{
		if(!neutralized)
		{
			HandleInput(input);

			currentTimeout -= elapsed.asSeconds();
			if(currentTimeout <= 0.f)
			{
				currentTimeout = cRingingTimeout;
				auto & sfx = ResourceCache::GetInstance().GetSoundBuffer("phone-ring");
				SoundManager::GetInstance().PlaySFX(sfx);
			}
		}

		obstacleSprite.Update(elapsed);

		Move(horizontalDisplacement, 0.f);
	}

	Base * Phone::Clone() const
	{
		return new Phone(*this);
	}

	Phone::Phone(const bool playerHasSensor)
		: GestureBase(4,
			50.f,
			Type::Phone,
			ResourceCache::GetInstance().GetSpriteSheet("phone"),
			playerHasSensor)
	{
	}
}
