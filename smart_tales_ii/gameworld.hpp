#pragma once
#include "gamemode.hpp"
#include "fonts.hpp"

#include <memory>
#include <string>
#include <vector>

class GameWorld : public sf::Drawable
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	Fonts & fonts;
	std::vector<std::shared_ptr<Gamemode>> gamemodes;
	unsigned int currentGamemodeIdx;
	
public:
	void Load();

	void Update(const sf::Time & timeElapsed,
		const Inputhandler & input,
		const sf::View & view);

	GameWorld(Fonts & fontsRef,
		const unsigned int windowWidth,
		const unsigned int windowHeight);
};
