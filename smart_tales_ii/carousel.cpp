#include "carousel.hpp"

#include "vectormath.hpp"

const float cTileSpacing = 50.f;
const float cTileYPos = 90.f;
// Maximum distance moved before a tap is no longer a tap but a swipe
const float cTapBias = 15.f;

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

void SaleTileCarousel::Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory)
{
	bool hasInteracted = false;

	if(input.PointingDevicePressedEvent())
	{
		wasMouseDown = true;
		mouseStartPosition = input.PointingDeviceWorldPosition();
		previousMousePosition = mouseStartPosition;
	}
	else if(input.PointingDeviceIsDown())
	{
		const float horizontalDistance = input.PointingDeviceWorldPosition().x - previousMousePosition.x;
		previousMousePosition = input.PointingDeviceWorldPosition();

		for(size_t i = 0; i < tiles.size(); ++i)
		{
			tiles[i]->Update(elapsed, input, inventory, horizontalDistance, false);
		}
	}
	else if(input.PointingDeviceReleasedEvent())
	{
		wasMouseDown = false;

		const float distanceTravelledTotal = VectorMathF::Distance(mouseStartPosition, input.PointingDeviceWorldPosition());
		if(distanceTravelledTotal < cTapBias)
		{
			for(size_t i = 0; i < tiles.size(); ++i)
			{
				hasInteracted = hasInteracted || tiles[i]->Update(elapsed, input, inventory, 0.f);
			}
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
	: leftTilePosition(cTileSpacing, cTileYPos)
{
}

