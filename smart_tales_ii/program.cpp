#include "program.hpp"
#include "runningmode.hpp"

#include <algorithm>
#include <cassert>
#include <iostream> // debug
#include <string>
#include <vector>

const std::vector<std::string> cFontFiles =
{
	"font/commodore.ttf"
};

const std::vector<std::string> cFontNames =
{
	"commodore"
};

void Program::Load()
{
	for(size_t i = 0U; i < cFontFiles.size(); ++i)
	{
		if(!fontsContainer.LoadFont(cFontFiles[i], cFontNames[i]))
		{
			throw std::runtime_error("Error loading file " + cFontFiles[i]);
		}
	}
	// Set game starting gamemode
	std::shared_ptr<Gamemode> startupmode(new RunningMode(fontsContainer, manager));
	manager.PushGamemode(startupmode);
}

void Program::Run()
{
	sf::Clock sfclock; // Don't do anything heavy after this (inb4 time warps)
	do
	{
		// start update
		inputhandler.Update(window);

		if(inputhandler.WasKeyReleased(sf::Keyboard::Key::Escape))
			break;

		manager.Update(sfclock.restart(), inputhandler, window.getView());
		// end update

		window.clear(sf::Color::White);
		// draw
		window.draw(manager);
		// end draw
		window.display();
	} while(!inputhandler.DidWindowClose());
}

Program::Program( const unsigned int _windowWidth,
						const unsigned int _windowHeight,
						const std::string windowTitle,
						const unsigned int frameRateLimit)
	: windowWidth(_windowWidth),
	windowHeight(_windowHeight),
	window(sf::VideoMode(_windowWidth, _windowHeight, 32U), windowTitle),
	inputhandler(),
	manager()
{
	window.setFramerateLimit(frameRateLimit);

	auto view = window.getView();
	view.setSize(_windowWidth, _windowHeight);
	view.setCenter(_windowWidth / 2, _windowHeight / 2);
	window.setView(view);
}

Program::~Program()
{
	window.close();
}
