#pragma once
#include "gamemode.hpp"

#include <memory>
#include <string>
#include <vector>

class GameWorld : public sf::Drawable
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	sf::Font * fontPtr;
	std::vector<std::shared_ptr<Gamemode>> gamemodes;
	unsigned int currentGamemodeIdx;
	
public:
	void Update(const sf::Time & timeElapsed,
		const Inputhandler & input,
		const sf::View & view);

	GameWorld(sf::Font * fontPointer,
		const unsigned int windowWidth,
		const unsigned int windowHeight);
};
