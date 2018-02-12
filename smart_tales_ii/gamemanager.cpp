#include "gamemanager.hpp"

#include <cassert>
#include <cmath>
#include <ctime>

void GameManager::Update(const sf::Time & timeElapsed,
	const Inputhandler & input,
	const sf::View & view)
{
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
		Gamemode & gamemode = *(gamemodes[i]);
		// This is done beforehand due to the gamemode potentially deleting itself in the update
		if(gamemode.SurpressUpdate())
		{
			gamemode.Update(timeElapsed, input);
			break;
		}
		gamemode.Update(timeElapsed, input);
	}
}

void GameManager::PushGamemode(Gamemode * gamemode)
{
	gamemode->Load();
	gamemode->OnEnter();
	gamemodes.emplace_back(gamemode);
}

bool GameManager::RemoveGamemode(Gamemode * gamemode)
{
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
		if(gamemodes[i].get() == gamemode)
		{
			gamemode->OnExit();
			gamemodes.erase(gamemodes.begin() + i);
			return true;
		}
	}

	return false;
}

void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Painters algorithm, so first figure out where to start
	int64_t start = 0;
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
		if(gamemodes[i]->SurpressDraw())
		{
			start = i;
			break;
		}
	}

	for(int64_t i = start; i < gamemodes.size(); ++i)
	{
		target.draw(*(gamemodes[i]), states);
	}
}

GameManager::GameManager()
: gamemodes()
{

}
