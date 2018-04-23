#include "program.hpp"
#include "runningmode.hpp"
#include "temporaryoverlay.hpp"
#include "uioverlay.hpp"

#include <array>
#include <algorithm>
#include <cassert>
#include <iostream> // debug
#include <string>

#pragma region Loadfiles
const std::array<std::string, 1> cFontFiles = {
	"font/commodore.ttf"
};

const std::array<std::string, 10> cTextureFiles = {
	"texture/coin.png",
	"texture/paperclip.png",
	"texture/passive_ir_beam.png",
	"texture/runningbackground.png",
	"texture/shopbackground.png",
	"texture/upgradetile_door.png",
	"texture/upgradetile_furniture.png",
	"texture/upgradetile_light.png",
	"texture/upgradetile_phone.png",
	"texture/upgradetilebg.png"
};

const std::array<std::string, 16> cSpriteSheetFiles = {
	"animation/active_ir.txt",
	"animation/door.txt",
	"animation/furniture.txt",
	"animation/light.txt",
	"animation/lightswitch.txt",
	"animation/livetile.txt",
	"animation/musicbutton.txt",
	"animation/navigationbutton_large.txt",
	"animation/passive_ir.txt",
	"animation/pausebutton.txt",
	"animation/phone.txt",
	"animation/player_legs.txt",
	"animation/player_upperbody.txt",
	"animation/purchasebutton.txt",
	"animation/scorebackground.txt",
	"animation/sfxbutton.txt"
};

const std::array<std::string, 2> cMusicFiles = {
	"music/casabossanova.ogg",
	"music/pixelland.ogg"
};

const std::array<std::string, 7> cAudioFiles = {
	"sfx/coin.ogg",
	"sfx/door-open.ogg",
	"sfx/kaching.ogg",
	"sfx/phone-pickup.ogg",
	"sfx/phone-ring.ogg",
	"sfx/switch.ogg",
	"sfx/woosh.ogg"
};
#pragma endregion

void Program::Load()
{
	auto & cache = ResourceCache::GetInstance();

	for(size_t i = 0U; i < cFontFiles.size(); ++i)
	{
		cache.LoadFont(cFontFiles[i]);
	}
	for(size_t i = 0U; i < cTextureFiles.size(); ++i)
	{
		cache.LoadTexture(cTextureFiles[i]);
	}
	for(size_t i = 0U; i < cSpriteSheetFiles.size(); ++i)
	{
		cache.LoadSpriteSheet(cSpriteSheetFiles[i]);
	}
	for(size_t i = 0U; i < cMusicFiles.size(); ++i)
	{
		cache.LoadMusic(cMusicFiles[i]);
	}
	for(size_t i = 0U; i < cAudioFiles.size(); ++i)
	{
		cache.LoadSound(cAudioFiles[i]);
	}

	// Set game starting gamemode
	auto & manager = GameManager::GetInstance();
	manager.PushGamemode(new RunningMode(Player::Inventory()));
	manager.PushGamemode(new TemporaryOverlay("Evade all obstacles!"));
}

void Program::Run()
{
	auto & manager = GameManager::GetInstance();
	sf::Clock sfclock; // Don't do anything heavy after this (inb4 time warps)
	do
	{
		// start update
		inputhandler.Update(window);

		manager.Update(sfclock.restart(), inputhandler, window.getView());
		// end update

		window.clear(sf::Color::Black);
		// draw
		window.draw(manager);
		// end draw
		window.display();
	} while(!inputhandler.DidWindowClose() && manager.gamemodes.size() > 0);
}

Program::Program( const unsigned int _windowWidth,
						const unsigned int _windowHeight,
						const std::string windowTitle,
						const bool isDebugging)
	: window(sf::VideoMode(_windowWidth, _windowHeight, 32U), windowTitle)
{
	//window.setFramerateLimit(frameRateLimit);
	window.setVerticalSyncEnabled(true);

	auto view = window.getView();
#pragma warning(suppress: 4244) // resolution should not exceed precision of float
	view.setSize(_windowWidth, _windowHeight);
#pragma warning(suppress: 4244) // half resolution should not exceed precision of float
	view.setCenter(_windowWidth / 2, _windowHeight / 2);
	window.setView(view);

	GameManager::GetInstance().SetDebugFlag(isDebugging);
}

Program::~Program()
{
	window.close();
}
