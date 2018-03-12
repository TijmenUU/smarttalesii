#include "shopmode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "runningmode.hpp"
#include "upgradetile.hpp"

#include <array>
#include <iostream> // debug
 
const std::array<Upgrade::Sensor, 4> cTileUpgrades = {
	Upgrade::Sensor::PassiveInfrared,
	Upgrade::Sensor::ActiveInfrared,
	Upgrade::Sensor::HealthBand,
	Upgrade::Sensor::LiveTile
};

const std::array<std::string, 4> cTileImageTextures = {
	"texture/upgradetile_image.png",
	"texture/upgradetile_image.png",
	"texture/upgradetile_image.png",
	"texture/upgradetile_image.png"
};

const std::array<std::string, 4> cTileDescriptions = {
	"Passive Infrared\nSensor",
	"Active Infrared\nSensor",
	"Health monitoring\nwristband",
	"Live tile"
};

const std::array<unsigned int, 4> cTilePrices = {
	400,
	600,
	800,
	1000
};

void ShopMode::LoadTiles()
{
	if(!tileBackgroundTexture.loadFromFile("texture/upgradetilebg.png"))
	{
		throw std::runtime_error("Error fetching upgradetilebg.png in Shopmode.");
	}

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in Shopmode.");
	}

	TextButton buttonTemplate;
	buttonTemplate.LoadFromFile("animation/purchasebutton.txt", purchaseButtonTexture);
	sf::Text buttonTemplateText("test", *fontPtr, 18U);
	buttonTemplate.SetText(buttonTemplateText);

	tileImageTextures.resize(cTileImageTextures.size());	
	for(size_t i = 0; i < tileImageTextures.size(); ++i)
	{
		if(!tileImageTextures[i].loadFromFile(cTileImageTextures[i]))
		{
			throw std::runtime_error("Error fetching <" + cTileImageTextures[i] + "> in Shopmode.");
		}

		UpgradeTile * upgradeTile = new UpgradeTile();
		upgradeTile->SetTileBackground(tileBackgroundTexture);
		upgradeTile->SetUpgrade(cTileUpgrades[i]);
		upgradeTile->SetImage(tileImageTextures[i]);
		upgradeTile->SetPrice(cTilePrices[i], *fontPtr);
		upgradeTile->SetDescription(cTileDescriptions[i], *fontPtr);
		upgradeTile->SetButton(buttonTemplate);	

		carousel.AddSaleTile(upgradeTile);
	}

	carousel.RefreshTiles(playerInventory);
}

void ShopMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(title, states);
	target.draw(gotoGameButton, states);
	target.draw(carousel, states);
}

void ShopMode::Load()
{
	manager.PopAllBelow(this);
	manager.PushGamemode(new UIOverlay(resourceCache, manager, false));

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in RunningMode.");
	}

	title.setFont(*fontPtr);
	title.setCharacterSize(48);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.f);
	title.setString("Shop");
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 0.f);

	gotoGameButton.LoadFromFile("animation/navigationbutton_large.txt", navigationButtonTexture);
	const auto buttonBounds = gotoGameButton.GetGlobalbounds();
	gotoGameButton.SetPosition(sf::Vector2f(Alignment::GetCenterOffset(buttonBounds.width, cWorldWidth / 2.f), cWorldHeight - (buttonBounds.height + 5.f)));
	sf::Text buttonText("Back to running", *fontPtr, 26U);
	buttonText.setFillColor(sf::Color::White);
	gotoGameButton.SetText(buttonText);

	LoadTiles();
}

void ShopMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	// debug
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		playerInventory.AddCurrency(40);
		std::cout << "Gave you 40 moneys, current balance is: " << playerInventory.GetCurrency() << '\n';
		carousel.RefreshTiles(playerInventory);
	}
	// end debug
	if(gotoGameButton.Update(elapsed, input))
	{
		manager.PushGamemode(new RunningMode(resourceCache, manager, playerInventory));
		return;
	}
	carousel.Update(elapsed, input, playerInventory);
}

ShopMode::ShopMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Inventory & inventory)
	:Gamemode(resourceCacheRef, managerRef),
	playerInventory(inventory),
	carousel(),
	title(),
	navigationButtonTexture(),
	gotoGameButton()
{
}
