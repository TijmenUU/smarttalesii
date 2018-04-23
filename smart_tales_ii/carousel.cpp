#include "carousel.hpp"

#include "gamemode.hpp" // for world dimensions
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
#pragma warning(suppress: 4244) // Tile count (size_t) should not exceed float precision in normal circumstances
		const float tileCount = static_cast<float>(tiles.size());
		tilePtr->SetPosition(sf::Vector2f(tileSize * tileCount + leftTilePosition.x, cTileYPos));
	}
	
	tiles.emplace_back(tilePtr);
}

void SaleTileCarousel::Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory)
{
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

		if(horizontalDistance == 0.f)
			return;

		if(horizontalDistance < 0.f)
		{
			const auto lastbounds = tiles.back()->GetGlobalBounds();
			if(lastbounds.left + lastbounds.width < cWorldWidth)
				return;
		}
		else
		{
			const auto firstbounds = tiles.front()->GetGlobalBounds();
			if(firstbounds.left > 0.f)
				return;
		}

		for(size_t i = 0; i < tiles.size(); ++i)
		{
			tiles[i]->Update(elapsed, horizontalDistance);
		}
	}
	else if(input.PointingDeviceReleasedEvent())
	{
		wasMouseDown = false;

		const float distanceTravelledTotal = VectorMathF::Distance(mouseStartPosition, input.PointingDeviceWorldPosition());
		if(distanceTravelledTotal < cTapBias)
		{
			bool hasInteracted = false;
			for(size_t i = 0; i < tiles.size(); ++i)
			{
				hasInteracted = hasInteracted || tiles[i]->HandleInput(input, inventory);
				if(hasInteracted)
				{
					RefreshTiles(inventory);
					return;
				}
			}
		}
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

