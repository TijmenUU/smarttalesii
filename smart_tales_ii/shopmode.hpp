#pragma once
#include "gamemode.hpp"

#include "carousel.hpp"
#include "currencydisplayer.hpp"
#include "playerinventory.hpp"
#include "textbutton.hpp"

#include <memory>

class ShopMode : public Gamemode
{
private:
	Player::Inventory playerInventory;

	sf::Sprite background;
	SaleTileCarousel carousel;
	CurrencyDisplayer currencyDisplay;
	
	TextButton gotoGameButton;

	void LoadTiles();

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ShopMode(const Player::Inventory & inventory);
};
