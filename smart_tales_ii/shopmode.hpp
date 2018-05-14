/*
	shopmode.hpp

	The shop gamemode class. It has a carousel of products and
	a button to return to the RunningMode gamemode.

	It has a few debug options:
		- keyboard key a to buy all upgrades
		- keyboard key m to gain currency

	It surpresses the update of underlying gamemodes
	It surpresses the drawing of underlying gamemodes
*/

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

	bool SurpressDraw() const override;
	bool SurpressUpdate() const override;

	void OnEnter() override;

public:
	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ShopMode(const Player::Inventory & inventory);
};
