#include "../gamemanager.hpp"
#include "uioverlay.hpp"

void UIOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(gamePauseButton.IsEnabled())
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

bool UIOverlay::SuppressUpdate() const
{
	return gamePauseButton.IsDown();
}

void UIOverlay::Setup()
{
	pauseOverlay.setPosition(0.f, 0.f);
	pauseOverlay.setFillColor(sf::Color(0, 0, 0, 65));

	auto & cache = ResourceCache::GetInstance();
	sf::Font & font = cache.GetFont("commodore");

	pauseText.setFont(font);
	pauseText.setCharacterSize(32);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(2.f);
	pauseText.setString("Game is paused");

	auto bounds = pauseText.getGlobalBounds();
	pauseText.setPosition(cWorldWidth / 2.f - bounds.width / 2.f, cWorldHeight / 2.f);

	const auto & smanager = SoundManager::GetInstance();
	const float buttonSpacing = 60.f + 15.f;
	sf::Vector2f buttonPosition(1280.f - buttonSpacing, 15.f);
	gamePauseButton.SetPosition(buttonPosition);
	buttonPosition.x -= buttonSpacing;
	musicMuteButton.SetPosition(buttonPosition);
	musicMuteButton.SetDown(smanager.IsMusicMuted());
	buttonPosition.x -= buttonSpacing;
	sfxMuteButton.SetPosition(buttonPosition);
	sfxMuteButton.SetDown(smanager.IsSFXMuted());
}

void UIOverlay::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(sfxMuteButton.HandleInput(input))
	{
		SoundManager::GetInstance().SetSFXMute(sfxMuteButton.IsDown());
	}
	else if(musicMuteButton.HandleInput(input))
	{
		SoundManager::GetInstance().SetMusicMute(musicMuteButton.IsDown());
	}
	else if(gamePauseButton.HandleInput(input))
	{
		auto & smanager = SoundManager::GetInstance();
		if(gamePauseButton.IsDown())
		{
			originalVolume = smanager.GetMusicVolume();
			smanager.SetMusicVolume(10.f);
		}
		else
		{
			smanager.SetMusicVolume(originalVolume);
		}
	}
}

UIOverlay::UIOverlay(const bool canPause)
	: pauseOverlay(sf::Vector2f(cWorldWidth, cWorldHeight)),
	sfxMuteButton(ResourceCache::GetInstance().GetSpriteSheet("sfxbutton")),
	musicMuteButton(ResourceCache::GetInstance().GetSpriteSheet("musicbutton")),
	gamePauseButton(ResourceCache::GetInstance().GetSpriteSheet("pausebutton"), canPause)
{
}
