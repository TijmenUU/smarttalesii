#include "playersprite.hpp"

#include <cassert>

const std::string cUpperBodyFile("animation/player_upperbody.txt");
const std::string cLegsFile("animation/player_legs.txt");

void PlayerSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(legsSprite, states);
	target.draw(upperBodySprite, states);
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

void PlayerSprite::Load()
{
	upperBodySheet.LoadFromFile(cUpperBodyFile);
	legsSheet.LoadFromFile(cLegsFile);

	SetAnimation("run");
}

void PlayerSprite::Update(const sf::Time & elapsed)
{
	legsSprite.Update(elapsed);
	upperBodySprite.Update(legsSprite); // body is parented to legs
}

PlayerSprite::PlayerSprite()
	: upperBodySheet(),
	legsSheet(),
	upperBodySprite(upperBodySheet),
	legsSprite(legsSheet)
{
}
