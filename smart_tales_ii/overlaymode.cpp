#include "overlaymode.hpp"

#include "gamemanager.hpp"

void OverlayMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(pauseEnabled)
	{
		if(gamePauseButton.IsDown())
		{
			target.draw(pauseOverlay, states);
			target.draw(pauseText, states);
		}
		target.draw(gamePauseButton, states);
	}
	target.draw(sfxMuteButton, states);
	target.draw(musicMuteButton, states);
}

bool OverlayMode::SurpressUpdate() const
{
	return gamePauseButton.IsDown();
}

void OverlayMode::Load()
{
	pauseOverlay.setPosition(0.f, 0.f);
	pauseOverlay.setFillColor(sf::Color(0, 0, 0, 65));

	sf::Font * fontPtr = resourceCache.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in PausedMode.");
	}

	pauseText.setFont(*fontPtr);
	pauseText.setCharacterSize(32);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(2.f);
	pauseText.setString("Game is paused");

	auto bounds = pauseText.getGlobalBounds();
	pauseText.setPosition(cWorldWidth / 2.f - bounds.width / 2.f, cWorldHeight / 2.f);

	gamePauseButton.LoadFromFile("animation/pausebutton.txt", gamePauseTexture);
	musicMuteButton.LoadFromFile("animation/musicbutton.txt", musicMuteTexture);
	sfxMuteButton.LoadFromFile("animation/sfxbutton.txt", sfxMuteTexture);

	const float buttonSpacing = 60.f + 15.f;
	sf::Vector2f buttonPosition(1280.f - buttonSpacing, 15.f);
	gamePauseButton.SetPosition(buttonPosition);
	buttonPosition.x -= buttonSpacing;
	musicMuteButton.SetPosition(buttonPosition);
	buttonPosition.x -= buttonSpacing;
	sfxMuteButton.SetPosition(buttonPosition);
}

void OverlayMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(sfxMuteButton.Update(elapsed, input))
	{
		// TODO do something with the changed mute state
	}
	else if(musicMuteButton.Update(elapsed, input))
	{
		// TODO do something with the changed mute state
	}
	else if(pauseEnabled && gamePauseButton.Update(elapsed, input))
	{
		// TODO do something with the changed paused state? (optionally)
	}
}

OverlayMode::OverlayMode(ResourceCache & resourceCacheRef, GameManager & managerRef, const bool canPause)
	: Gamemode(resourceCacheRef, managerRef),
	pauseOverlay(sf::Vector2f(cWorldWidth, cWorldHeight)),
	pauseText(),
	pauseEnabled(canPause),
	sfxMuteTexture(), 
	musicMuteTexture(), 
	gamePauseTexture(),
	sfxMuteButton(),
	musicMuteButton(),
	gamePauseButton(canPause)
{
}
