#pragma once
#include "resourcecache.hpp"
#include "gamemanager.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

class Program
{
private:
	sf::RenderWindow window;
	Inputhandler inputhandler;
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
