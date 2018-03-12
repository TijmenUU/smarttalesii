#pragma once
#include "button.hpp"
#include "gamemode.hpp"

class UIOverlay : public Gamemode
{
private:
	sf::RectangleShape pauseOverlay;
	sf::Text pauseText;
	const bool pauseEnabled;

	sf::Texture sfxMuteTexture, musicMuteTexture, gamePauseTexture;

	Button sfxMuteButton;
	Button musicMuteButton;
	Button gamePauseButton;

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
