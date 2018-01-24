#pragma once
#include "gameworld.hpp"
#include "inputhandler.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

class Program
{
protected:
	unsigned int windowWidth, windowHeight;
	sf::RenderWindow window;
	sf::Font defaultFont;

	Inputhandler inputhandler;
	GameWorld world;
public:
	void Run();

	Program(const unsigned int _windowWidth,
		const unsigned int _windowHeight,
		const std::string fontLocation = "consola.ttf",
		const std::string windowTitle = "test",
		const unsigned int frameRateLimit = 60U);
	~Program();
};
