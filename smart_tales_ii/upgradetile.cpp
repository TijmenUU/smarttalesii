#include "upgradetile.hpp"

#include <iomanip>
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

void UpgradeTile::UpdateButton(const Player::Inventory & inventory)
{
	if(inventory.HasSensorUpgrade(upgrade))
	{
		purchaseButton.Disable();
		purchaseButton.SetAnimation("bought");
		purchaseButton.SetString("Bought");
	}
	else if(!inventory.CanAfford(upgradePrice))
	{
		purchaseButton.Disable();
		purchaseButton.SetAnimation("too-expensive");
		purchaseButton.SetString("Can't\nafford");
	}
	else
	{
		purchaseButton.Enable();
		purchaseButton.SetAnimation("buy");
		purchaseButton.SetString("Buy");
	}
}

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
	upgrade = s;
}

void UpgradeTile::SetImage(const sf::Texture & t)
{
	upgradeImage.setTexture(t, true);
}

void UpgradeTile::SetPrice(const unsigned int price, sf::Font & font)
{
	upgradePrice = price;
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4);
	ss << price;

	upgradePriceText.setFont(font);
	upgradePriceText.setString(ss.str());
}

void UpgradeTile::SetPrice(const unsigned int price, const sf::Text & text)
{
	upgradePrice = price;
	upgradePriceText = text;
}

void UpgradeTile::SetDescription(const std::string & description, sf::Font & font)
{
	upgradeDescription.setFont(font);
	upgradeDescription.setString(description);
	//upgradeDescription.set
}

void UpgradeTile::SetDescription(const sf::Text & text)
{
	upgradeDescription = text;
}

void UpgradeTile::SetButton(const TextButton & toCopy)
{
	purchaseButton = toCopy;
}

void UpgradeTile::Refresh(const Player::Inventory & inventory)
{
	UpdateButton(inventory);
}

bool UpgradeTile::Update(const sf::Time & elapsed, const Inputhandler & input, Player::Inventory & inventory, const float horizontalDisplacement)
{
	bool retval = false;
	if(purchaseButton.Update(elapsed, input))
	{
		inventory.RemoveCurrency(upgradePrice);
		inventory.AddSensorUpgrade(upgrade);
		UpdateButton(inventory);

		retval = true;
	}

	if(horizontalDisplacement != 0)
	{
		sf::Vector2f newposition = tileSprite.getPosition();
		newposition.x += horizontalDisplacement;
		SetPosition(newposition);
	}

	return retval;
}
