#pragma once
#include "inputhandler.hpp"
#include "playerinventory.hpp"

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>

class SaleTile : public sf::Drawable
{
private:
	sf::Vector2f position;
	std::vector<std::unique_ptr<sf::Drawable>> drawables;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	virtual void SetPosition(const float x, const float y);
	virtual sf::Vector2f GetPosition() const;

	// Returns whether the interaction was handled
	virtual bool Update(const sf::Time & elapsed, 
		const Inputhandler & input, 
		Player::Inventory & inventory, 
		const float horizontalDisplacement) = 0;

	SaleTile();
	virtual ~SaleTile() = default;
};
