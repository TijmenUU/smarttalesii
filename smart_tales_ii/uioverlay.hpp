/*
	uioverlay.hpp

	The overlay that has 3 buttons to:
	- Toggle mute sound effects
	- Toggle mute music
	- Toggle pause

	It surpresses the update of underlying gamemodes 
	when the pause button is toggled.
	It does not surpress the drawing of underlying gamemodes
*/

#pragma once
#include "button.hpp"
#include "gamemode.hpp"

#include <list>
#include <memory>

class UIOverlay : public Gamemode
{
private:
	sf::RectangleShape pauseOverlay;
	sf::Text pauseText;
	float originalVolume;

	Button sfxMuteButton, musicMuteButton, gamePauseButton;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	bool SuppressUpdate() const override;
	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	UIOverlay(const bool canPause = true);
};
