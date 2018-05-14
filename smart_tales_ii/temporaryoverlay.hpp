/*
	temporaryoverlay.hpp

	An overlay that presents a piece of text and deletes itself
	automatically after the lifetime is equal or greater than
	the set timeout.

	It does not surpress the update of underlying gamemodes
	It does not surpress the drawing of underlying gamemodes
*/

#pragma once
#include "gamemode.hpp"

class TemporaryOverlay : public Gamemode
{
private:
	sf::Text text;
	const float timeout;
	float currentTime = 0.f;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	void Setup() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	TemporaryOverlay(const std::string & message,
		const float timeOutInSeconds = 3.f);
};

