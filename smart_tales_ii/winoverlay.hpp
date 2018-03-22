#pragma once
#include "gamemode.hpp"

class WinOverlay : public Gamemode
{
private:
	float idleTimeOut;
	uint8_t fadeIncrement = 3U;
	uint8_t colorValue = 0U;
	sf::Text title;
	sf::Text body;
	sf::RectangleShape background;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	void Show();

	WinOverlay(const float timeOut = 15.f);
};