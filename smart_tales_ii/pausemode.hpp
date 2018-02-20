#pragma once
#include "gamemode.hpp"

class PauseMode : public Gamemode
{
private:
	sf::Text pauseText;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	bool SurpressUpdate() const override;
	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	PauseMode(Fonts & fontsRef, GameManager & managerRef, const std::string message = "Press P to unpause");
	~PauseMode() override = default;
};
