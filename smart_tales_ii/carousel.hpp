#pragma once
#include "tile.hpp"

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
