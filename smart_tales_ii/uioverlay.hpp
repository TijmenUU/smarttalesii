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
	const bool pauseEnabled;

	Animation::Sheet sheetStorage[3];

	std::unique_ptr<Button> sfxMuteButton, musicMuteButton, gamePauseButton;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	bool SurpressUpdate() const override;
	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	UIOverlay(ResourceCache & resourceCacheRef, 
		GameManager & managerRef, 
		const bool canPause = true);
};
