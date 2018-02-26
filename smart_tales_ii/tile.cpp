#include "tile.hpp"

void SaleTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(size_t i = 0; i < drawables.size(); ++i)
	{
		target.draw(*(drawables[i]), states);
	}
}

void SaleTile::SetPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
}

sf::Vector2f SaleTile::GetPosition() const
{
	return position;
}

SaleTile::SaleTile()
	: position(0.f, 0.f),
	drawables()
{
}