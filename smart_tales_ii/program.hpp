#pragma once
#include "fonts.hpp"
#include "gameworld.hpp"
#include "inputhandler.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

class Program
{
private:
	unsigned int windowWidth, windowHeight;
	sf::RenderWindow window;
	Fonts fontsContainer;

	Inputhandler inputhandler;
	GameWorld world;

public:
	// May throw a runtime exception if it cannot load the required files and assets
	void Load();

	void Run();

	Program(const unsigned int _windowWidth,
		const unsigned int _windowHeight,
		const std::string windowTitle = "test",
		const unsigned int frameRateLimit = 60U);
	~Program();
};
