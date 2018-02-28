#pragma once
#include "tile.hpp"

class SaleTileCarousel : public sf::Drawable
{
private:
	float scrollingSpeed;
	bool wasMouseDown;
	sf::Vector2f previousMousePosition;
	sf::Vector2f leftTilePosition;
	std::vector<std::unique_ptr<SaleTile>> tiles;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void AddSaleTile(SaleTile * tilePtr);

	// Returns whether one of the tiles had an interaction
	bool Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory);

	void RefreshTiles(const Player::Inventory & inventory);

	SaleTileCarousel();
	virtual ~SaleTileCarousel() = default;
};
