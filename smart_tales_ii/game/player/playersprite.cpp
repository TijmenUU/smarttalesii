#include "../resourcecache.hpp"
#include <cassert>
#include "playersprite.hpp"

const float cShowoffLength = 1.f;

void PlayerSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(legsSprite, states);
	target.draw(upperBodySprite, states);
}

void PlayerSprite::ShowOff()
{
	showingOff = true;
	upperBodySprite.SetAnimation("run-showoff");
}

bool PlayerSprite::SetAnimation(const std::string & name)
{
	return upperBodySprite.SetAnimation(name) && legsSprite.SetAnimation(name);
}

void PlayerSprite::SetPosition(const sf::Vector2f & p)
{
	upperBodySprite.setPosition(p);
	legsSprite.setPosition(p);
}

const sf::Vector2f & PlayerSprite::GetPosition() const
{
	return upperBodySprite.getPosition();
}

sf::FloatRect PlayerSprite::GetGlobalBounds() const
{
	return upperBodySprite.getGlobalBounds();
}

void PlayerSprite::Update(const sf::Time & elapsed)
{
	if(showingOff)
	{
		showoffTimer += elapsed.asSeconds();
		if(showoffTimer >= cShowoffLength)
		{
			showingOff = false;
			showoffTimer = 0.f;
			upperBodySprite.SetAnimation("run-enhanced");
		}
	}
	legsSprite.Update(elapsed);
	upperBodySprite.Update(legsSprite); // body is parented to legs
}

PlayerSprite::PlayerSprite(const Player::Inventory & inventory)
	: upperBodySprite(ResourceCache::GetInstance().GetSpriteSheet("player_upperbody")),
	legsSprite(ResourceCache::GetInstance().GetSpriteSheet("player_legs"))
{
	if(inventory.HasSensorUpgrade(Upgrade::Sensor::HealthBand))
	{
		legsSprite.SetAnimation("run");
		upperBodySprite.SetAnimation("run-enhanced");
	}
	else
	{
		SetAnimation("run");
	}
}
