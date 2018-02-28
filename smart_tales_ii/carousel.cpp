#include "carousel.hpp"

#include "vectormath.hpp"

const float cTileSpacing = 50.f;
const float cTileYPos = 90.f;
const float cMinimumScrollDistance = 5.f;

void SaleTileCarousel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for(size_t i = 0; i < tiles.size(); ++i)
	{
		target.draw(*(tiles[i]), states);
	}
}

bool SaleTileCarousel::UpdateScroll(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory)
{
	if(input.PointingDevicePressedEvent())
	{
		wasMouseDown = true;
		previousMousePosition = input.PointingDeviceWorldPosition();
	}
	else if(input.PointingDeviceIsDown())
	{
		const float horizontalDistance = input.PointingDeviceWorldPosition().x - previousMousePosition.x;
		previousMousePosition = input.PointingDeviceWorldPosition();

		if(std::abs(horizontalDistance) > cMinimumScrollDistance)
		{
			for(size_t i = 0; i < tiles.size(); ++ i)
			{
				tiles[i]->Update(elapsed, input, inventory, horizontalDistance, false);
			}
			return true;
		}
	}
	else
	{
		wasMouseDown = false;
	}

	return false;
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

void SaleTileCarousel::Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory)
{
	bool hasInteracted = false;
	if(!UpdateScroll(elapsed, input, inventory))
	{
		for(size_t i = 0; i < tiles.size(); ++i)
		{
			hasInteracted = hasInteracted || tiles[i]->Update(elapsed, input, inventory, 0.f);
		}
	}

	if(hasInteracted)
	{
		RefreshTiles(inventory);
	}
}

void SaleTileCarousel::RefreshTiles(const Player::Inventory & inventory)
{
	for(size_t i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Refresh(inventory);
	}
}

SaleTileCarousel::SaleTileCarousel()
	: wasMouseDown(false),
	previousMousePosition(0.f, 0.f),
	leftTilePosition(cTileSpacing, cTileYPos),
	tiles()
{
}

