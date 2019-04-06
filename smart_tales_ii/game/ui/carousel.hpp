/*
	carousel.hpp

	A simple horizontal scrolling carousel of SaleTile objects
	and derrived ones.

	It limits the scrolling to the leftmost (first) and rightmost
	(last) tiles. So if instantiated with few tiles it may not
	scroll at all if it fits the window width.

	The scrolling is done by moving a minimal amount (bias) whilst the
	pointing device is down. If it is less than the bias, it simply
	handles it as a click event for one of the tiles.
*/

#pragma once
#include "salestile.hpp"

class SaleTileCarousel : public sf::Drawable
{
private:
	bool wasMouseDown = false;
	sf::Vector2f mouseStartPosition = sf::Vector2f(0.f, 0.f);
	sf::Vector2f previousMousePosition = sf::Vector2f(0.f, 0.f);
	sf::Vector2f leftTilePosition;
	std::vector<std::unique_ptr<SaleTile>> tiles;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void AddSaleTile(SaleTile * tilePtr);

	void Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory);

	void RefreshTiles(const Player::Inventory & inventory);

	SaleTileCarousel();
	virtual ~SaleTileCarousel() = default;
};
