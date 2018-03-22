#include "upgradetile.hpp"

#include <iomanip>
#include <iostream> // debug
#include <sstream>

/* Tile layout */
const sf::Vector2f cImagePosition(35, 35);
const sf::Vector2f cPaperclipPosition(0, -40);
const sf::Vector2f cPricePosition(260, 90);
const sf::Vector2f cButtonPosition(250, 130);
const sf::Vector2f cDescriptionPosition(70, 270);

void UpgradeTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(image, states);
	target.draw(paperclip, states);
	if(!purchaseButton.IsPurchased())
		target.draw(upgradePriceText, states);
	target.draw(purchaseButton, states);
	target.draw(upgradeDescription, states);
}

void UpgradeTile::SetPosition(const sf::Vector2f & p)
{
	background.setPosition(p);
	image.setPosition(p + cImagePosition);
	paperclip.setPosition(p + cPaperclipPosition);
	upgradePriceText.setPosition(p + cPricePosition);
	purchaseButton.SetPosition(p + cButtonPosition);
	upgradeDescription.setPosition(p + cDescriptionPosition);
}

sf::Vector2f UpgradeTile::GetPosition() const
{
	return background.getPosition();
}

sf::Vector2f UpgradeTile::GetSize() const
{
	const auto bounds = background.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
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
		sf::Vector2f newposition = background.getPosition();
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

UpgradeTile::UpgradeTile(const Upgrade::Sensor upgrade,
	const unsigned int price,
	const std::string & description,
	const sf::Texture & backgroundTexture,
	const sf::Texture & productImage,
	const sf::Texture & paperclipTexture,
	Animation::Sheet & purchaseButtonSheet,
	sf::Font & font)
	: SaleTile(font),
	background(backgroundTexture),
	image(productImage),
	paperclip(paperclipTexture),
	upgradePriceText("", font, 30U),
	purchaseButton(upgrade, price, purchaseButtonSheet),
	upgradeDescription(description, font, 26U)
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(3);
	ss << price;

	const sf::Color textColor(0, 15, 85);

	upgradePriceText.setString(ss.str());
	upgradePriceText.setFillColor(textColor);

	upgradeDescription.setFillColor(textColor);
}
