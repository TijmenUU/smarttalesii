#include "program.hpp"

#include <algorithm>
#include <cassert>
#include <iostream> // debug

void Program::Run()
{

	sf::Clock sfclock; // Don't do anything heavy after this (inb4 time warps)
	do
	{
		// start update
		inputhandler.Update(window);

		if(inputhandler.WasKeyReleased(sf::Keyboard::Key::Escape))
			break;

		world.Update(sfclock.restart(), inputhandler, window.getView());
		// end update

		window.clear(sf::Color::White);
		// draw
		window.draw(world);
		// end draw
		window.display();
	} while(!inputhandler.DidWindowClose());
}

Program::Program( const unsigned int _windowWidth,
						const unsigned int _windowHeight,
						const std::string fontLocation,
						const std::string windowTitle,
						const unsigned int frameRateLimit)
	: windowWidth(_windowWidth),
	windowHeight(_windowHeight),
	window(sf::VideoMode(_windowWidth, _windowHeight, 32U), windowTitle),
	inputhandler(),
	world(&defaultFont, _windowWidth, _windowHeight)
{
	window.setFramerateLimit(frameRateLimit);

	defaultFont.loadFromFile(fontLocation);
}

Program::~Program()
{
	window.close();
}
