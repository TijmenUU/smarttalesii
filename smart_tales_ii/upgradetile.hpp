#pragma once
#include "tile.hpp"
#include "upgrades.hpp"
#include "purchasebutton.hpp"

#include <string>

class UpgradeTile : public SaleTile
{
private:
	sf::Sprite background;
	sf::Sprite image;
	sf::Sprite paperclip;
	sf::Text upgradePriceText;
	PurchaseButton purchaseButton;
	sf::Text upgradeDescription;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetPosition(const sf::Vector2f & p) override;
	virtual sf::Vector2f GetPosition() const override;
	virtual sf::Vector2f GetSize() const override;

	void Refresh(const Player::Inventory & inventory) override;

	// Returns whether the interaction was handled
	bool Update(const sf::Time & elapsed,
		const Inputhandler & input,
		Player::Inventory & inventory,
		const float horizontalDisplacement,
		const bool allowInteraction = true) override;

	UpgradeTile(const Upgrade::Sensor upgrade,
		const unsigned int price,
		const std::string & description,
		const sf::Texture & backgroundTexture,
		const sf::Texture & productImage,
		const sf::Texture & paperclipTexture,
		Animation::Sheet & purchaseButtonSheet, 
		sf::Font & font);
};

