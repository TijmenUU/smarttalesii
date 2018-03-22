#include "playersprite.hpp"

#include <cassert>

const std::string cUpperBodyFile("animation/player_upperbody.txt");
const std::string cLegsFile("animation/player_legs.txt");

const float cShowoffLength = 1.f;

void PlayerSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(legsSprite, states);
	target.draw(upperBodySprite, states);
}

bool PlayerSprite::IsShowingOff() const
{
	return showingOff;
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

void PlayerSprite::Load(const Player::Inventory & inventory)
{
	upperBodySheet.LoadFromFile(cUpperBodyFile);
	legsSheet.LoadFromFile(cLegsFile);

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

PlayerSprite::PlayerSprite()
	: upperBodySprite(upperBodySheet),
	legsSprite(legsSheet)
{
}
