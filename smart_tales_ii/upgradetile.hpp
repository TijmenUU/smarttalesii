#pragma once
#include "tile.hpp"
#include "upgrades.hpp"
#include "purchasebutton.hpp"

class UpgradeTile : public SaleTile
{
private:
	sf::Sprite tileSprite;
	sf::Sprite upgradeImage;
	sf::Text upgradePriceText;
	PurchaseButton purchaseButton;
	sf::Text upgradeDescription;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetPosition(const sf::Vector2f & p) override;
	virtual sf::Vector2f GetPosition() const override;
	virtual sf::Vector2f GetSize() const override;

	void SetTileBackground(const sf::Texture & t);
	void SetUpgrade(const Upgrade::Sensor s);
	void SetImage(const sf::Texture & t);
	void SetPrice(const unsigned int price);
	void SetDescription(const std::string & description);

	void Refresh(const Player::Inventory & inventory) override;

	// Returns whether the interaction was handled
	bool Update(const sf::Time & elapsed,
		const Inputhandler & input,
		Player::Inventory & inventory,
		const float horizontalDisplacement,
		const bool allowInteraction = true) override;

	UpgradeTile(const Animation::Sheet & purchaseButtonSheet, sf::Font & font);
};

