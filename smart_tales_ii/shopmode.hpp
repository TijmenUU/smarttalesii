#pragma once
#include "gamemode.hpp"

#include "carousel.hpp"
#include "playerinventory.hpp"

class ShopMode : public Gamemode
{
private:
	Player::Inventory playerInventory;

	std::vector<sf::Texture> tileImageTextures;
	sf::Texture tileBackgroundTexture;
	sf::Texture purchaseButtonTexture;
	SaleTileCarousel carousel;
	sf::Text title;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void LoadTiles();

public:
	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

	ShopMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Inventory & inventory);
};
