#pragma once
#include "gamemode.hpp"

#include "carousel.hpp"
#include "playerinventory.hpp"
#include "textbutton.hpp"

#include <memory>

class ShopMode : public Gamemode
{
private:
	Player::Inventory playerInventory;

	sf::Texture tileBackgroundTexture;
	std::vector<sf::Texture> tileImageTextures;
	Animation::Sheet purchaseButtonSheet;
	Animation::Sheet navigationButtonSheet;

	SaleTileCarousel carousel;
	sf::Text title;
	
	std::unique_ptr<TextButton> gotoGameButton;

	void LoadTiles();

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ShopMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Inventory & inventory);
};
