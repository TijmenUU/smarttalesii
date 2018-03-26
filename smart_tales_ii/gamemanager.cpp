#include "gamemanager.hpp"

#include <cassert>
#include <cmath>
#include <ctime>

void GameManager::Update(const sf::Time & elapsed,
	const Inputhandler & input,
	const sf::View & view)
{
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		Gamemode & gamemode = *(gamemodes[i]);
		// This is done beforehand due to the gamemode potentially deleting itself in the update
		if(gamemode.SurpressUpdate())
		{
			gamemode.Update(elapsed, input);
			break;
		}
		gamemode.Update(elapsed, input);
	}
}

GameManager & GameManager::GetInstance()
{
	static GameManager m;
	return m;
}

void GameManager::PushGamemode(Gamemode * gamemode)
{
	gamemodes.emplace_back(gamemode);
	gamemode->Setup();
	gamemode->OnEnter();
}

bool GameManager::RemoveGamemode(Gamemode * gamemode)
{
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		if(gamemodes[i].get() == gamemode)
		{
			gamemode->OnExit();
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
			gamemodes.erase(gamemodes.begin() + i);
			return true;
		}
	}

	return false;
}

void GameManager::Pop()
{
	if(gamemodes.size() > 0)
	{
		gamemodes.erase(gamemodes.end() - 1);
	}
}

bool GameManager::PopUntill(Gamemode * gamemode)
{
	while(gamemodes.size() > 0 && gamemodes.back().get() != gamemode)
	{
		Pop();
	}
	if(gamemodes.size() > 0)
	{
		Pop();
		return true;
	}

	return false;
}

bool GameManager::PopAllBelow(Gamemode * gamemode)
{
	while(gamemodes.size() > 0 && gamemodes.front().get() != gamemode)
	{
		gamemodes.erase(gamemodes.begin());
	}
	return false;
}

void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Painters algorithm, so first figure out where to start
	int64_t start = 0;
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		if(gamemodes[i]->SurpressDraw())
		{
			start = i;
			break;
		}
	}

	for(int64_t i = start; i < gamemodes.size(); ++i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		target.draw(*(gamemodes[i]), states);
	}
}
