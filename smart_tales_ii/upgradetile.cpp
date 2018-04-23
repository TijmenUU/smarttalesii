#include "upgradetile.hpp"

#include "alignmenthelp.hpp"
#include "resourcecache.hpp"
#include "soundmanager.hpp"

#include <iomanip>
#include <iostream> // debug
#include <sstream>

/* Tile layout */
const sf::Vector2f cImagePosition(35, 35);
const sf::Vector2f cPaperclipPosition(0, -40);
const sf::Vector2f cPricePosition(310, 107);
const sf::Vector2f cButtonPosition(250, 130);
const sf::Vector2f cDescriptionCenter(245, 395);

void UpgradeTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(image, states);
	target.draw(paperclip, states);
	if(!purchaseButton.IsPurchased())
		target.draw(priceText, states);
	target.draw(purchaseButton, states);
	target.draw(upgradeDescription, states);
}

void UpgradeTile::SetPosition(const sf::Vector2f & p)
{
	background.setPosition(p);
	image.setPosition(p + cImagePosition);
	paperclip.setPosition(p + cPaperclipPosition);
	priceText.CenterOn(p + cPricePosition);
	purchaseButton.SetPosition(p + cButtonPosition);

	const auto bounds = upgradeDescription.getLocalBounds();
	upgradeDescription.setPosition(Alignment::GetCenterOffset(bounds.width, p.x + cDescriptionCenter.x) + bounds.left, p.y + 300.f);
}

sf::Vector2f UpgradeTile::GetPosition() const
{
	return background.getPosition();
}

sf::FloatRect UpgradeTile::GetGlobalBounds() const
{
	return background.getGlobalBounds();
}

void UpgradeTile::Refresh(const Player::Inventory & inventory)
{
	purchaseButton.Refresh(inventory);
}

bool UpgradeTile::HandleInput(const Inputhandler & input, Player::Inventory & inventory)
{
	if(purchaseButton.HandleInput(input))
	{
		inventory.RemoveCurrency(purchaseButton.GetPrice());
		std::cout << "Bought upgrade for " << purchaseButton.GetPrice() << " moneys, making your balance " << inventory.GetCurrency() << ".\n"; // debug
		inventory.AddSensorUpgrade(purchaseButton.GetUpgrade());
		auto & sfx = ResourceCache::GetInstance().GetSoundBuffer("kaching");
		SoundManager::GetInstance().PlaySFX(sfx);

		return true;
	}
	return false;
}

void UpgradeTile::Update(const sf::Time & elapsed, 
	const float horizontalDisplacement)
{
	sf::Vector2f newposition = background.getPosition();
	newposition.x += horizontalDisplacement;
	SetPosition(newposition);
}

UpgradeTile::UpgradeTile(const Upgrade::Sensor upgrade,
	const unsigned int price,
	const std::string & description,
	const sf::Texture & productImage,
	sf::Font & font)
	: background(ResourceCache::GetInstance().GetTexture("upgradetilebg")),
	image(productImage),
	paperclip(ResourceCache::GetInstance().GetTexture("paperclip")),
	priceText(3U),
	purchaseButton(upgrade, price),
	upgradeDescription(description, font, 26U)
{
	priceText.SetValue(price, false);
	
	upgradeDescription.setFillColor(sf::Color::White);
	upgradeDescription.setOutlineColor(sf::Color::Black);
	upgradeDescription.setOutlineThickness(2.f);
}
