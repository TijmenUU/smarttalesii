#include "../../util/alignmenthelp.hpp"
#include "../gamemanager.hpp"
#include "../overlay/uioverlay.hpp"
#include "../resourcecache.hpp"
#include "../ui/upgradetile.hpp"
#include <array>
#include <cstdio> // for debug mode
#include "runningmode.hpp"
#include "shopmode.hpp"

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
	"This detects\nmovement and\nautomatically\nturns on the\nlights!",
	"Doors like in\nsupermarkets,\nfully automated!",
	"Allow the doctor\nto monitor my\ncondition without\na call!",
	"Automagical\nremoval of\nin-the-way\nfurniture!"
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
	target.draw(currencyDisplay, states);
	target.draw(gotoGameButton, states);
	target.draw(carousel, states);
}

bool ShopMode::SuppressDraw() const
{
	return true;
}

bool ShopMode::SuppressUpdate() const
{
	return true;
}

void ShopMode::OnEnter()
{
	auto & music = ResourceCache::GetInstance().GetMusic("casabossanova");
	music.setVolume(50);
	music.setLoop(true);
	SoundManager::GetInstance().CrossFadeMusic(music);
}

void ShopMode::Setup()
{
	auto & manager = GameManager::GetInstance();
	manager.PopAllBelow(this);
	manager.PushGamemode(std::make_unique<UIOverlay>(false));

	background.setPosition(0.f, 0.f);

	auto & font = ResourceCache::GetInstance().GetFont("commodore");

	currencyDisplay.SetValue(playerInventory.GetCurrency(), false);
	currencyDisplay.CenterOn(cWorldWidth / 2.f, 25.f);

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
	if(GameManager::GetInstance().GetDebugFlag())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			playerInventory.AddCurrency(40);
			currencyDisplay.SetValue(playerInventory.GetCurrency(), false);
			std::printf("Gave you 40 money, current balance is: %u\n", playerInventory.GetCurrency());
			carousel.RefreshTiles(playerInventory);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			for(size_t i = 0; i < cTileUpgrades.size(); ++i)
			{
				playerInventory.AddSensorUpgrade(cTileUpgrades[i]);
			}
			carousel.RefreshTiles(playerInventory);
			std::puts("Unlocked all upgradedes!");
		}
	}

	if(gotoGameButton.HandleInput(input))
	{
		GameManager::GetInstance().PushGamemode(std::make_unique<RunningMode>(playerInventory));
		return;
	}

	const auto currency = playerInventory.GetCurrency();
	carousel.Update(elapsed, input, playerInventory);
	if(currency != playerInventory.GetCurrency())
	{
		currencyDisplay.SetValue(playerInventory.GetCurrency());
	}
	else
	{
		currencyDisplay.Update(elapsed);
	}
}

ShopMode::ShopMode(const Player::Inventory & inventory)
	: playerInventory(inventory),
	background(ResourceCache::GetInstance().GetTexture("shopbackground")),
	gotoGameButton(ResourceCache::GetInstance().GetSpriteSheet("navigationbutton_large"))
{
}
