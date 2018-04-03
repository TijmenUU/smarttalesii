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

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
protected:
	friend class Program;

	void Update(const sf::Time & elapsed,
		const Inputhandler & input,
		const sf::View & view);

public:
	static GameManager & GetInstance();
	// Calls Load on gamemode, thus it may throw an runtime_error exception
	void PushGamemode(Gamemode * gamemode);
	bool RemoveGamemode(Gamemode * gamemode);
	void Pop();
	// Inclusive, pops until it finds gamemode, pops that too and then stops
	bool PopUntill(Gamemode * gamemode);
	bool PopAllBelow(Gamemode * gamemode);

	GameManager() = default;
	GameManager(const GameManager &) = delete;
	GameManager(const GameManager &&) = delete;
	GameManager & operator = (GameManager &) = delete;
	GameManager & operator = (GameManager &&) = delete;
};
