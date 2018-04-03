#include "gamemanager.hpp"

#include <cassert>
#include <cmath>
#include <ctime>

void GameManager::Update(const sf::Time & elapsed,
	const Inputhandler & input,
	const sf::View & view)
{
	// update sound fx as well
	for(int64_t i = static_cast<int64_t>(soundEffects.size()) - 1; i >= 0; --i)
	{
		if(soundEffects[i].getStatus() != sf::SoundSource::Playing)
		{
			soundEffects.erase(soundEffects.begin() + i);
		}
	}

	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		Gamemode & gamemode = *(gamemodes[i]);
		// This is done beforehand due to the gamemode potentially deleting itself in the update
		if(gamemode.SurpressUpdate())
		{
			gamemode.Update(elapsed, input);
			break;
		}
		gamemode.Update(elapsed, input);
	}
}

GameManager & GameManager::GetInstance()
{
	static GameManager m;
	return m;
}

void GameManager::PushGamemode(Gamemode * gamemode)
{
	gamemodes.emplace_back(gamemode);
	gamemode->Setup();
	gamemode->OnEnter();
}

bool GameManager::RemoveGamemode(Gamemode * gamemode)
{
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		if(gamemodes[i].get() == gamemode)
		{
			gamemode->OnExit();
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
			gamemodes.erase(gamemodes.begin() + i);
			return true;
		}
	}

	return false;
}

void GameManager::Pop()
{
	if(gamemodes.size() > 0)
	{
		gamemodes.back()->OnExit();
		gamemodes.erase(gamemodes.end() - 1);
	}
}

bool GameManager::PopUntill(Gamemode * gamemode)
{
	while(gamemodes.size() > 0 && gamemodes.back().get() != gamemode)
	{
		Pop();
	}
	if(gamemodes.size() > 0)
	{
		Pop();
		return true;
	}

	return false;
}

bool GameManager::PopAllBelow(Gamemode * gamemode)
{
	while(gamemodes.size() > 0 && gamemodes.front().get() != gamemode)
	{
		gamemodes.front()->OnExit();
		gamemodes.erase(gamemodes.begin());
	}
	return false;
}

void GameManager::StopMusic()
{
	if(currentMusicPtr != nullptr)
	{
		currentMusicPtr->stop();
	}
}

void GameManager::PlayMusic(sf::Music & music)
{
	if(musicMuted)
	{
		return;
	}

	if(currentMusicPtr != nullptr)
	{
		currentMusicPtr->stop();
	}
	currentMusicPtr = &music;
	currentMusicPtr->play();
}

float GameManager::GetMusicVolume() const
{
	if(currentMusicPtr != nullptr)
	{
		return currentMusicPtr->getVolume();
	}
	return -1.f;
}

void GameManager::SetMusicVolume(const float volume)
{
	if(currentMusicPtr != nullptr)
	{
		currentMusicPtr->setVolume(volume);
	}
}

void GameManager::SetMucicMute(const bool muted)
{
	musicMuted = muted;
	if(musicMuted)
	{
		StopMusic();
	}
	else
	{
		if(currentMusicPtr != nullptr)
		{
			currentMusicPtr->play();
		}
	}
}

bool GameManager::IsMusicMuted() const
{
	return musicMuted;
}

void GameManager::PlaySFX(const sf::SoundBuffer & buffer, const float volume)
{
	// Limit the number of simultaneous sound effects, 256 according to the SFML
	// docs but we stay way clear of that number. 256 is including any music tracks
	// playing.
	if(sfxMuted || soundEffects.size() > 128)
	{
		return;
	}

	soundEffects.emplace_back(buffer);
	soundEffects.back().setVolume(volume);
	soundEffects.back().play();
}

void GameManager::SetSFXMuted(const bool muted)
{
	sfxMuted = muted;
	if(sfxMuted)
	{
		soundEffects.clear();
	}
}

bool GameManager::IsSFXMuted() const
{
	return sfxMuted;
}

void GameManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Painters algorithm, so first figure out where to start
	int64_t start = 0;
	for(int64_t i = static_cast<int64_t>(gamemodes.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		if(gamemodes[i]->SurpressDraw())
		{
			start = i;
			break;
		}
	}

	for(int64_t i = start; i < gamemodes.size(); ++i)
	{
#pragma warning(suppress: 4244) // gamemodes size should not exceed int64_t precision
		target.draw(*(gamemodes[i]), states);
	}
}
