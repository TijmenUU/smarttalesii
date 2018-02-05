#pragma once
#include "gamemode.hpp"
#include "fonts.hpp"

#include <memory>
#include <string>
#include <vector>

class GameWorld : public sf::Drawable
{
private:
	Fonts & fonts;
	std::vector<std::shared_ptr<Gamemode>> gamemodes;
	unsigned int currentGamemodeIdx;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
public:
	// May throw a runtime exception if it cannot load the required files and assets
	void Load();

	void Update(const sf::Time & timeElapsed,
		const Inputhandler & input,
		const sf::View & view);

	GameWorld(Fonts & fontsRef,
		const unsigned int windowWidth,
		const unsigned int windowHeight);
};
