#include "soundmanager.hpp"

#include <cassert>
#include <cmath>

void SoundManager::StopAllSounds()
{
	for(size_t i = 0; i < sounds.size(); ++i)
	{
		sounds[i].stop();
	}
}

void SoundManager::InsertSound(const sf::SoundBuffer & buffer, const float volume)
{
	for(auto & sound : sounds)
	{
		if(sound.getStatus() == sf::SoundStream::Stopped)
		{
			sound.setBuffer(buffer);
			sound.setVolume(volume);
			sound.play();
			break;
		}
	}
}

void SoundManager::Update(const sf::Time & elapsed)
{
	if(fadeTime > 0.f)
	{
		const float step = elapsed.asSeconds();
		fadeTime -= step;
		currentMusicPtr->setVolume(std::max(0.f,currentMusicPtr->getVolume() - step * fadeOutVolumePerSecond));
		nextMusicPtr->setVolume(std::min(100.f, nextMusicPtr->getVolume() + step * fadeInVolumePerSecond));
		if(fadeTime < 0.f)
		{
			fadeTime = 0.f;
			currentMusicPtr->stop();
			currentMusicPtr = nextMusicPtr;
			nextMusicPtr = nullptr;

			currentMusicPtr->setVolume(fadeTargetVolume);
			if(!musicMuted)
				currentMusicPtr->play();
		}
	}
}

SoundManager & SoundManager::GetInstance()
{
	static SoundManager manager;

	return manager;
}

void SoundManager::StopMusic()
{
	if(currentMusicPtr != nullptr)
	{
		currentMusicPtr->stop();
		fadeTime = 0.f;
	}
}

void SoundManager::PlayMusic(sf::Music & music)
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

void SoundManager::CrossFadeMusic(sf::Music & next, const float time)
{
	if(musicMuted) // if muted we don't fade, we just switch and not play
	{
		fadeTime = 0.f;
		currentMusicPtr = &next;
		return;
	}

	if(currentMusicPtr == nullptr) // Nothing to cross fade into
	{
		fadeTime = 0.f;
		PlayMusic(next);
		return;
	}

	fadeTargetVolume = next.getVolume();
	assert(fadeTargetVolume >= 0.f && fadeTargetVolume <= 100.f);
	fadeTime = time;
	fadeInVolumePerSecond = fadeTargetVolume / time;
	fadeOutVolumePerSecond = currentMusicPtr->getVolume() / time;
	nextMusicPtr = &next;
}

float SoundManager::GetMusicVolume() const
{
	if(currentMusicPtr != nullptr)
	{
		return currentMusicPtr->getVolume();
	}
	return -1.f;
}

void SoundManager::SetMusicVolume(const float volume)
{
	assert(volume >= 0.f && volume <= 100.f);
	if(currentMusicPtr != nullptr)
	{
		currentMusicPtr->setVolume(volume);
	}
}

void SoundManager::SetMusicMute(const bool muted)
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

bool SoundManager::IsMusicMuted() const
{
	return musicMuted;
}

void SoundManager::PlaySFX(const sf::SoundBuffer & buffer, const float volume)
{
	assert(volume >= 0.f && volume <= 100.f);
	// Limit the number of simultaneous sound effects, 256 according to the SFML
	// docs but we stay way clear of that number. 256 is including any music tracks
	// playing.
	if(sfxMuted)
	{
		return;
	}

	InsertSound(buffer, volume);
}

void SoundManager::SetSFXMute(const bool muted)
{
	sfxMuted = muted;
	if(sfxMuted)
	{
		StopAllSounds();
	}
}

bool SoundManager::IsSFXMuted() const
{
	return sfxMuted;
}
