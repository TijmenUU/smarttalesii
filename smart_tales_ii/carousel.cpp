#include "carousel.hpp"

const float cTileSpacing = 50.f;
const float cTileYPos = 90.f;

void SaleTileCarousel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(size_t i = 0; i < tiles.size(); ++i)
	{
		target.draw(*(tiles[i]), states);
	}
}

void SaleTileCarousel::AddSaleTile(SaleTile * tilePtr)
{
	if(tiles.size() == 0)
	{
		tilePtr->SetPosition(leftTilePosition);
	}
	else
	{
		const float tileSize = 450.f + cTileSpacing;
		const float tileCount = tiles.size();
		tilePtr->SetPosition(sf::Vector2f(tileSize * tileCount + leftTilePosition.x, cTileYPos));
	}
	
	tiles.emplace_back(tilePtr);
}

bool SaleTileCarousel::Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory)
{
	bool hasInteracted = false;
	for(int64_t i = static_cast<int64_t>(tiles.size()) - 1; i >= 0; --i)
	{
		hasInteracted = hasInteracted || (tiles[i])->Update(elapsed, input, inventory, 0.f); // TODO add scroll
	}

	if(hasInteracted)
	{
		RefreshTiles(inventory);
	}

	return hasInteracted;
}

void SaleTileCarousel::RefreshTiles(const Player::Inventory & inventory)
{
	for(size_t i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Refresh(inventory);
	}
}

SaleTileCarousel::SaleTileCarousel()
	: scrollingSpeed(0.f),
	wasMouseDown(false),
	previousMousePosition(0.f, 0.f),
	leftTilePosition(cTileSpacing, cTileYPos),
	tiles()
{
}

