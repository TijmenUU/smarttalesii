#pragma once
#include "fonts.hpp"
#include "gameworld.hpp"
#include "inputhandler.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

class Program
{
protected:
	unsigned int windowWidth, windowHeight;
	sf::RenderWindow window;
	Fonts fontsContainer;

	Inputhandler inputhandler;
	GameWorld world;
public:
	void Load();

	void Run();

	Program(const unsigned int _windowWidth,
		const unsigned int _windowHeight,
		const std::string windowTitle = "test",
		const unsigned int frameRateLimit = 60U);
	~Program();
};
