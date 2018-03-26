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
	"upgradetile_light",
	"upgradetile_door",
	"upgradetile_phone",
	"upgradetile_furniture"
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
	auto & cache = ResourceCache::GetInstance();
	auto & font = cache.GetFont("commodore");

	for(size_t i = 0; i < cTileImageTextures.size(); ++i)
	{
		UpgradeTile * upgradeTile = new UpgradeTile(
			cTileUpgrades[i],
			cTilePrices[i],
			cTileDescriptions[i],
			cache.GetTexture(cTileImageTextures[i]),
			font);

		carousel.AddSaleTile(upgradeTile);
	}

	// Important to set the purchase button states after changing prices!
	carousel.RefreshTiles(playerInventory);
}

void ShopMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(title, states);
	target.draw(gotoGameButton, states);
	target.draw(carousel, states);
}

void ShopMode::Setup()
{
	auto & manager = GameManager::GetInstance();
	manager.PopAllBelow(this);
	manager.PushGamemode(new UIOverlay(false));

	background.setPosition(0.f, 0.f);

	auto & font = ResourceCache::GetInstance().GetFont("commodore");

	title.setFont(font);
	title.setCharacterSize(48);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2.f);
	title.setString("Shop");
	title.setPosition(Alignment::GetCenterOffset(title.getGlobalBounds().width, cWorldWidth / 2.f), 0.f);

	const auto buttonBounds = gotoGameButton.GetGlobalbounds();
	gotoGameButton.SetPosition(sf::Vector2f(Alignment::GetCenterOffset(buttonBounds.width, cWorldWidth / 2.f), cWorldHeight - (buttonBounds.height + 5.f)));
	sf::Text buttonText("Back to running", font, 30U);
	buttonText.setOutlineThickness(2.f);
	buttonText.setOutlineColor(sf::Color(120, 63, 0));
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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for(size_t i = 0; i < cTileUpgrades.size(); ++i)
		{
			playerInventory.AddSensorUpgrade(cTileUpgrades[i]);
		}
		carousel.RefreshTiles(playerInventory);
		std::cout << "Unlocked all upgradedes!\n";
	}
	// end debug
	if(gotoGameButton.HandleInput(input))
	{
		GameManager::GetInstance().PushGamemode(new RunningMode(playerInventory));
		return;
	}
	carousel.Update(elapsed, input, playerInventory);
}

ShopMode::ShopMode(const Player::Inventory & inventory)
	: playerInventory(inventory),
	background(ResourceCache::GetInstance().GetTexture("shopbackground")),
	gotoGameButton(ResourceCache::GetInstance().GetSpriteSheet("navigationbutton_large"))
{
}
