#pragma once
#include "fonts.hpp"
#include "gamemode.hpp"

#include <memory>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>

class GameManager : public sf::Drawable
{
private:
	std::vector<std::shared_ptr<Gamemode>> gamemodes;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
protected:
	friend class Program;

	void Update(const sf::Time & timeElapsed,
		const Inputhandler & input,
		const sf::View & view);

public:
	// Calls Load on gamemode, thus it may throw an runtime_error exception
	void PushGamemode(std::shared_ptr<Gamemode> gamemode);
	bool RemoveGamemode(std::shared_ptr<Gamemode> gamemode);

	GameManager();
};
