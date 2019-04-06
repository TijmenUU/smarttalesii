/*
	winoverlay.hpp

	The overlay presented to the player when he has
	all upgrades purchased in the RunningMode gamemode

	It does not surpress the update of underlying gamemodes
	It does not surpress the drawing of underlying gamemodes
*/

#pragma once
#include "../ui/informationcard.hpp"
#include "gamemode.hpp"

class WinOverlay : public Gamemode
{
private:
	float idleTimeOut;
	uint8_t fadeIncrement = 3U;
	uint8_t colorValue = 0U;
	sf::Text title;
	InformationCard first, second, third;
	sf::RectangleShape background;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	void Show();

	WinOverlay(const float timeOut = 15.f, const float cardTimeOut = 1.8f);
};