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

