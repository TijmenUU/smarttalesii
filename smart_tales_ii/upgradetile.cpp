#include "upgradetile.hpp"

#include <iomanip>
#include <iostream> // debug
#include <sstream>

/* Tile layout */
const sf::Vector2f cTileSize(450, 535);
const sf::Vector2f cImageSize(200, 200);
const sf::Vector2f cImagePosition(35, 35);
const sf::Vector2f cPriceSize(145, 82);
const sf::Vector2f cPricePosition(270, 35);
const sf::Vector2f cButtonPosition(270, 117);
const sf::Vector2f cButtonSize(145, 82);
const sf::Vector2f cDescriptionPosition(35, 270);
const sf::Vector2f cDescriptionSize(380, 230);

void UpgradeTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(tileSprite, states);
	target.draw(upgradeImage, states);
	target.draw(upgradePriceText, states);
	target.draw(purchaseButton, states);
	target.draw(upgradeDescription, states);
}

void UpgradeTile::SetPosition(const sf::Vector2f & p)
{
	tileSprite.setPosition(p);
	upgradeImage.setPosition(p + cImagePosition);
	upgradePriceText.setPosition(p + cPricePosition);
	purchaseButton.SetPosition(p + cButtonPosition);
	upgradeDescription.setPosition(p + cDescriptionPosition);
}

sf::Vector2f UpgradeTile::GetPosition() const
{
	return tileSprite.getPosition();
}

sf::Vector2f UpgradeTile::GetSize() const
{
	return cTileSize;
}

void UpgradeTile::SetTileBackground(const sf::Texture & t)
{
	tileSprite.setTexture(t, true);
}

void UpgradeTile::SetUpgrade(const Upgrade::Sensor s)
{
	purchaseButton.SetUpgrade(s);
}

void UpgradeTile::SetImage(const sf::Texture & t)
{
	upgradeImage.setTexture(t, true);
}

void UpgradeTile::SetPrice(const unsigned int price)
{
	purchaseButton.SetPrice(price);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4);
	ss << price;

	upgradePriceText.setString(ss.str());
}

void UpgradeTile::SetDescription(const std::string & description)
{
	upgradeDescription.setString(description);
	//upgradeDescription.set
}

void UpgradeTile::Refresh(const Player::Inventory & inventory)
{
	purchaseButton.Refresh(inventory);
}

bool UpgradeTile::Update(const sf::Time & elapsed, 
	const Inputhandler & input, 
	Player::Inventory & inventory, 
	const float horizontalDisplacement,
	const bool allowInteraction)
{
	if(horizontalDisplacement != 0.f)
	{
		sf::Vector2f newposition = tileSprite.getPosition();
		newposition.x += horizontalDisplacement;
		SetPosition(newposition);
	}
	else if(allowInteraction && purchaseButton.HandleInput(input))
	{
		inventory.RemoveCurrency(purchaseButton.GetPrice());
		std::cout << "Bought upgrade for " << purchaseButton.GetPrice() << " moneys, making your balance " << inventory.GetCurrency() << ".\n"; // debug
		inventory.AddSensorUpgrade(purchaseButton.GetUpgrade());

		return true;
	}

	return false;
}

UpgradeTile::UpgradeTile(const Animation::Sheet & purchaseButtonSheet, sf::Font & font)
	: SaleTile(font),
	purchaseButton(purchaseButtonSheet)
{
	upgradePriceText.setFont(font);
	purchaseButton.SetFont(font);
	upgradeDescription.setFont(font);
}
