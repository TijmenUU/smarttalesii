#include "carousel.hpp"

const float cTileSpacing = 50.f;

void SaleTileCarousel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(size_t i = 0; i < tiles.size(); ++i)
	{
		target.draw(*(tiles[i]), states);
	}
}

void SaleTileCarousel::AddSaleTile(SaleTile * tilePtr)
{
	tiles.emplace_back(tilePtr);
}

bool SaleTileCarousel::RemoveSaleTile(SaleTile * tilePtr)
{
	for(size_t i = 0; i < tiles.size(); ++i)
	{
		if(tiles[i].get() == tilePtr)
		{
			tiles.erase(tiles.begin() + i);
			return true;
		}
	}
	return false;
}

void SaleTileCarousel::Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory)
{
	bool hasInteracted = false;
	for(int64_t i = static_cast<int64_t>(tiles.size()) - 1; i >= 0; --i)
	{
		hasInteracted = hasInteracted || (tiles[i])->Update(elapsed, input, inventory, 0.f);
	}
}

SaleTileCarousel::SaleTileCarousel()
	: scrollingSpeed(0.f),
	wasMouseDown(false),
	previousMousePosition(0.f, 0.f),
	leftTilePosition(50.f, 0.f),
	tiles()
{
}

