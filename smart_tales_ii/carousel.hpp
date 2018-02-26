#pragma once
#include "tile.hpp"

class SaleTileCarousel : public sf::Drawable
{
private:
	float scrollingSpeed;
	bool wasMouseDown;
	sf::Vector2f previousMousePosition;
	std::vector<std::unique_ptr<SaleTile>> tiles;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void AddSaleTile(SaleTile * tilePtr);
	bool RemoveSaleTile(SaleTile * tilePtr);

	void Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory);

	SaleTileCarousel();
	~SaleTileCarousel() = default;
};
