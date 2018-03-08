#pragma once
#include "inputhandler.hpp"
#include "playerinventory.hpp"

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>

class SaleTile : public sf::Drawable
{
protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

public:
	virtual void SetPosition(const sf::Vector2f & p) = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual sf::Vector2f GetSize() const = 0;

	virtual void Refresh(const Player::Inventory & inventory) = 0;

	// Returns whether the interaction was handled
	virtual bool Update(const sf::Time & elapsed, 
		const Inputhandler & input, 
		Player::Inventory & inventory, 
		const float horizontalDisplacement,
		const bool allowInteraction = true) = 0;

	SaleTile() = default;
	virtual ~SaleTile() = default;
};