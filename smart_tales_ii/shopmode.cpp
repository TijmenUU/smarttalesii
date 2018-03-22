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
	"texture/upgradetile_light.png",
	"texture/upgradetile_door.png",
	"texture/upgradetile_phone.png",
	"texture/upgradetile_furniture.png"
};

const std::array<std::string, 4> cTileDescriptions = {
	"Passive Infrared\nSensor",
	"Active Infrared\nSensor",
	"Health monitoring\nwristband",
	"Live tile"
};

const std::array<unsigned int, 4> cTilePrices = {
	200,
	250,
	300,
	400
};

void ShopMode::LoadTiles()
{
	if(!tileBackgroundTexture.loadFromFile("texture/upgradetilebg.png"))
	{
		throw std::runtime_error("Error fetching upgradetilebg.png in Shopmode.");
	}
	if(!paperclipTexture.loadFromFile("texture/paperclip.png"))
	{
		throw std::runtime_error("Error fetching paperclip.png in Shopmode.");
	}

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in Shopmode.");
	}

	sf::Text buttonTemplateText("test", *fontPtr, 18U);

	tileImageTextures.resize(cTileImageTextures.size());	
	for(size_t i = 0; i < tileImageTextures.size(); ++i)
	{
		if(!tileImageTextures[i].loadFromFile(cTileImageTextures[i]))
		{
			throw std::runtime_error("Error fetching <" + cTileImageTextures[i] + "> in Shopmode.");
		}

		UpgradeTile * upgradeTile = new UpgradeTile(
			cTileUpgrades[i],
			cTilePrices[i],
			cTileDescriptions[i],
			tileBackgroundTexture,
			tileImageTextures[i],
			paperclipTexture,
			purchaseButtonSheet, 
			*fontPtr);

		carousel.AddSaleTile(upgradeTile);
	}

	// Important to set the purchase button states after changing prices!
	carousel.RefreshTiles(playerInventory);
}

void ShopMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(title, states);
	target.draw(*gotoGameButton, states);
	target.draw(carousel, states);
}

void ShopMode::Load()
{
	manager.PopAllBelow(this);
	manager.PushGamemode(new UIOverlay(resourceCache, manager, false));

	if(!backgroundTexture.loadFromFile("texture/shopbackground.png"))
	{
		throw std::runtime_error("Error loading texture/shopbackground.png in Shopmode.");
	}
	background.setTexture(backgroundTexture, true);
	background.setPosition(0.f, 0.f);

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in Shopmode.");
	}

	title.setFont(*fontPtr);
	title.setCharacterSize(48);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.f);
	title.setString("Shop");
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 0.f);

	purchaseButtonSheet.LoadFromFile("animation/purchasebutton.txt");
	navigationButtonSheet.LoadFromFile("animation/navigationbutton_large.txt");
	gotoGameButton = std::make_unique<TextButton>(navigationButtonSheet);

	const auto buttonBounds = gotoGameButton->GetGlobalbounds();
	gotoGameButton->SetPosition(sf::Vector2f(Alignment::GetCenterOffset(buttonBounds.width, cWorldWidth / 2.f), cWorldHeight - (buttonBounds.height + 5.f)));
	sf::Text buttonText("Back to running", *fontPtr, 30U);
	buttonText.setOutlineThickness(1.f);
	buttonText.setOutlineColor(sf::Color(120, 63, 0));
	buttonText.setFillColor(sf::Color(181, 105, 0));
	gotoGameButton->SetText(buttonText);

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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for(size_t i = 0; i < cTileUpgrades.size(); ++i)
		{
			playerInventory.AddSensorUpgrade(cTileUpgrades[i]);
		}
		carousel.RefreshTiles(playerInventory);
	}
	// end debug
	if(gotoGameButton->HandleInput(input))
	{
		manager.PushGamemode(new RunningMode(resourceCache, manager, playerInventory));
		return;
	}
	carousel.Update(elapsed, input, playerInventory);
}

ShopMode::ShopMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const Player::Inventory & inventory)
	:Gamemode(resourceCacheRef, managerRef),
	playerInventory(inventory)
{
}
