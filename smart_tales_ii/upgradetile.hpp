#pragma once
#include "tile.hpp"
#include "upgrades.hpp"
#include "textbutton.hpp"

class UpgradeTile : public SaleTile
{
private:
	Upgrade::Sensor upgrade;
	sf::Sprite tileSprite;
	sf::Sprite upgradeImage;
	unsigned int upgradePrice;
	sf::Text upgradePriceText;
	TextButton purchaseButton;
	sf::Text upgradeDescription;

	void UpdateButton(const Player::Inventory & inventory);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void SetPosition(const sf::Vector2f & p) override;
	virtual sf::Vector2f GetPosition() const override;
	virtual sf::Vector2f GetSize() const override;

	void SetTileBackground(const sf::Texture & t);
	void SetUpgrade(const Upgrade::Sensor s);
	void SetImage(const sf::Texture & t);
	void SetPrice(const unsigned int price, sf::Font & font);
	void SetPrice(const unsigned int price, const sf::Text & text);
	void SetDescription(const std::string & description, sf::Font & font);
	void SetDescription(const sf::Text & text);
	void SetButtonText(const sf::Text & text);

	void Refresh(const Player::Inventory & inventory) override;

	// Returns whether the interaction was handled
	bool Update(const sf::Time & elapsed,
		const Inputhandler & input,
		Player::Inventory & inventory,
		const float horizontalDisplacement,
		const bool allowInteraction = true) override;

	UpgradeTile(const Animation::Sheet & purchaseButtonSheet);
};

