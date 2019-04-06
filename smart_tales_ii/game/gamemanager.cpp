#include "gamemanager.hpp"

void GameManager::Update(const sf::Time & elapsed,
	const Inputhandler & input,
	const sf::View & view)
{
	SoundManager::GetInstance().Update(elapsed);

	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{

		Gamemode & gamemode = *(gamemodes[i]);
		// This is done beforehand due to the gamemode potentially deleting itself in the update
		if(gamemode.SuppressUpdate())
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

void GameManager::PushGamemode(std::unique_ptr<Gamemode> && gamemode)
{
	gamemodes.emplace_back(std::move(gamemode));
	// Store the object before calling the Setup and OnEnter functions as these
	// may put new gamemodes on this stack!
	auto * insertedMode = gamemodes.back().get();
	insertedMode->Setup();
	insertedMode->OnEnter();
}

bool GameManager::RemoveGamemode(Gamemode * const gamemode)
{
	for(auto iter = gamemodes.begin(); iter != gamemodes.end(); ++iter)
	{
		if(iter->get() == gamemode)
		{
			gamemode->OnExit();
			gamemodes.erase(iter);
			return true;
		}
	}

	return false;
}

void GameManager::Pop()
{
	if(gamemodes.size() > 0)
	{
		gamemodes.back()->OnExit();
		gamemodes.erase(gamemodes.end() - 1);
	}
}

void GameManager::PopAllAbove(const Gamemode * const gamemode)
{
	while(gamemodes.size() > 0 && gamemodes.back().get() != gamemode)
	{
		Pop();
	}
}

void GameManager::PopAllBelow(const Gamemode * const gamemode)
{
	while(gamemodes.size() > 0 && gamemodes.front().get() != gamemode)
	{
		gamemodes.front()->OnExit();
		gamemodes.erase(gamemodes.begin());
	}
}

void GameManager::SetDebugFlag(const bool flag)
{
	debugFlag = flag;
}

bool GameManager::GetDebugFlag() const
{
	return debugFlag;
}

void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Painters algorithm, so first figure out where to start
	int64_t start = 0;
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{

		if(gamemodes[i]->SuppressDraw())
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
