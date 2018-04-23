#pragma once
#include "salestile.hpp"

#include "currencydisplayer.hpp"
#include "purchasebutton.hpp"
#include "upgrades.hpp"

#include <string>

class UpgradeTile : public SaleTile
{
private:
	sf::Sprite background;
	sf::Sprite image;
	sf::Sprite paperclip;
	CurrencyDisplayer priceText;
	PurchaseButton purchaseButton;
	sf::Text upgradeDescription;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetPosition(const sf::Vector2f & p) override;
	virtual sf::Vector2f GetPosition() const override;
	virtual sf::FloatRect GetGlobalBounds() const override;

	void Refresh(const Player::Inventory & inventory) override;

	// Returns whether the interaction was handled
	bool HandleInput(const Inputhandler & input, Player::Inventory & inventory) override;

	void Update(const sf::Time & elapsed,
		const float horizontalDisplacement) override;

	UpgradeTile(const Upgrade::Sensor upgrade,
		const unsigned int price,
		const std::string & description,
		const sf::Texture & productImage,
		sf::Font & font);
};

