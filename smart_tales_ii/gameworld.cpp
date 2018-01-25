#include "gameworld.hpp"
#include "runningmode.hpp"

#include <cmath>
#include <ctime>

void GameWorld::Update(const sf::Time & timeElapsed,
	const Inputhandler & input,
	const sf::View & view)
{
	gamemodes[currentGamemodeIdx]->Update(timeElapsed, input);
}

void GameWorld::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*(gamemodes[currentGamemodeIdx]), states);
}

GameWorld::GameWorld(sf::Font * fontPointer,
	const unsigned int windowWidth,
	const unsigned int windowHeight)
: fontPtr(fontPointer),
gamemodes(0),
currentGamemodeIdx(0U)
{
	gamemodes.emplace_back(new Runningmode());

	for(size_t i = 0; i < gamemodes.size(); ++i)
	{
		gamemodes[i]->Load();
	}
}
