#pragma once
#include "button.hpp"
#include "gamemode.hpp"

class OverlayMode : public Gamemode
{
private:
	sf::RectangleShape pauseOverlay;
	sf::Text pauseText;
	const bool pauseEnabled;

	sf::Texture sfxMuteTexture, musicMuteTexture, gamePauseTexture;

	Button sfxMuteButton;
	Button musicMuteButton;
	Button gamePauseButton;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	bool SurpressUpdate() const override;
	void Load() override;
	void Update(const sf::Time & elapsed, const Inputhandler & input) override;

public:
	OverlayMode(ResourceCache & resourceCacheRef, 
		GameManager & managerRef, 
		const bool canPause = true);
};
