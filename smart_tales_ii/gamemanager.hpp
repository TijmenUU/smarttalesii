/*
	gamemanager.hpp

	The Gamemanager class keeps a stack of active gamemodes. Later 
	gamemodes added are "on top" of the stack and are thus updated
	before the other gamemodes.

	A gamemode may surpress the update and drawing of the gamemodes "below" it.

	The debug flag is also stored in the manager class

	Don't use the constructor, use GameManager::GetInstance instead
*/

#pragma once
#include "gamemode.hpp"
#include "resourcecache.hpp"
#include "soundmanager.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GameManager : public sf::Drawable
{
private:
	std::vector<std::unique_ptr<Gamemode>> gamemodes;
	bool debugFlag = false;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
protected:
	friend class Program;

	void Update(const sf::Time & elapsed,
		const Inputhandler & input,
		const sf::View & view);

public:
	static GameManager & GetInstance();
	// Calls Load on gamemode, thus it may throw an runtime_error exception
	void PushGamemode(Gamemode * const gamemode);
	bool RemoveGamemode(Gamemode * const gamemode);
	// Pops the top element (added last) from the gamestate
	// stack
	void Pop();
	// Pops everything "above" (added later) the provided
	// pointer. If the pointer does not exist in the gamestate stack
	// the entire stack will be popped.
	void PopAllAbove(const Gamemode * const gamemode);
	// Pops everything "below" (added before) the provided
	// pointer. If the pointer does not exist in the gamestate stack
	// the entire stack will be popped.
	void PopAllBelow(const Gamemode * const gamemode);

	void SetDebugFlag(const bool flag);
	bool GetDebugFlag() const;

	GameManager() = default;
	GameManager(const GameManager &) = delete;
	GameManager(const GameManager &&) = delete;
	GameManager & operator = (GameManager &) = delete;
	GameManager & operator = (GameManager &&) = delete;
};
