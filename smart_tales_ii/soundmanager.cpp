#include "soundmanager.hpp"

#include <cassert>
#include <cstdio> // DEBUG DEBUG DEBUG

void SoundManager::StopAllSounds()
{
	for(size_t i = 0; i < sounds.size(); ++i)
	{
		sounds[i].stop();
	}
}

void SoundManager::InsertSound(const sf::SoundBuffer & buffer, const float volume)
{
	// Limit the number of simultaneous sound effects, 256 according to the SFML
	// docs but we stay way clear of that number. 256 is including any music tracks
	// playing.
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
	if(currentFadeTime < fadeTime)
	{
		currentFadeTime += elapsed.asSeconds();
		if(currentFadeTime > fadeTime)
		{
			currentMusicPtr->stop();
			currentMusicPtr = nextMusicPtr;
			currentMusicPtr->setVolume(fadeTime * fadeInVolumePerSecond);
			nextMusicPtr = nullptr;
		}
		else
		{
			currentMusicPtr->setVolume((fadeTime - currentFadeTime) * fadeOutVolumePerSecond);
			nextMusicPtr->setVolume(currentFadeTime * fadeInVolumePerSecond);
		}
	}
}

SoundManager::SoundManager()
	: currentMusicPtr(nullptr),
	nextMusicPtr(nullptr),
	musicMuted(false),
	sfxMuted(false),
	fadeTime(0.f),
	currentFadeTime(0.f),
	fadeInVolumePerSecond(0.f),
	fadeOutVolumePerSecond(0.f),
	sounds()
{
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

		// Handle possible cross fading currently going on
		if(nextMusicPtr != nullptr)
		{
			currentMusicPtr = nextMusicPtr;
			currentMusicPtr->stop();
			currentMusicPtr->setVolume(fadeTime * fadeInVolumePerSecond);
			nextMusicPtr = nullptr;

			currentFadeTime = 1.f;
			fadeTime = 0.f;
		}
	}
}

void SoundManager::PlayMusic(sf::Music & music)
{
	if(currentMusicPtr != nullptr)
	{
		currentMusicPtr->stop();
	}
	currentMusicPtr = &music;

	if(musicMuted)
	{
		std::puts("SoundManager::PlayMusic: music is muted."); // DEBUG
		return;
	}
	std::puts("SoundManager::PlayMusic: playing music."); // DEBUG
	currentMusicPtr->play();
}

void SoundManager::CrossFadeMusic(sf::Music & next, const float time)
{
	if(musicMuted) // if muted we don't fade, we just switch and not play
	{
		fadeTime = 0.f;
		currentFadeTime = 1.f;
		currentMusicPtr = &next;
		std::puts("Not cross fading because music is muted."); // DEBUG
		return;
	}

	if(currentMusicPtr == nullptr || time <= 0.f) // Nothing to cross fade into
	{
		fadeTime = 0.f;
		currentFadeTime = 1.f;
		currentMusicPtr = &next;
		currentMusicPtr->play();
		std::puts("Not cross fading because no music is playing."); // DEBUG
		return;
	}

	if(currentFadeTime < fadeTime)
	{
		if(&next == nextMusicPtr)
		{
			std::puts("Not cross fading because already cross fading to given music."); // DEBUG
			return;
		}
		std::puts("Was already cross fading, moving next into current..."); // DEBUG
		// We're crossfading while we're crossfading: bad!
		currentMusicPtr->stop();
		currentMusicPtr = nextMusicPtr;
	}

	std::puts("Cross fading into new music normally."); // DEBUG
	currentFadeTime = 0.f;
	fadeTime = time;
	fadeInVolumePerSecond = next.getVolume() / time;
	fadeOutVolumePerSecond = currentMusicPtr->getVolume() / time;
	
	nextMusicPtr = &next;
	nextMusicPtr->setVolume(0.f);
	nextMusicPtr->play();
}

float SoundManager::GetMusicVolume() const
{
	if(currentMusicPtr != nullptr)
	{
		return currentMusicPtr->getVolume();
	}
	return 0.f;
}

void SoundManager::SetMusicVolume(const float volume)
{
	std::printf("SoundManager::SetMusicVolume: set volume to %f.\n", volume); // DEBUG
	assert(volume >= 0.f && volume <= 100.f);
	if(currentMusicPtr != nullptr)
	{
		if(volume <= 0.f)
		{
			StopMusic();
		}
		else if(currentFadeTime < fadeTime)
		{
			fadeInVolumePerSecond  = volume / fadeTime;
			fadeOutVolumePerSecond = volume / fadeTime;
			// Actual volumes are updated next Update tick
		}
		else
		{
			currentMusicPtr->setVolume(volume);
		}
	}
}

void SoundManager::SetMusicMute(const bool muted)
{
	musicMuted = muted;
	if(musicMuted)
	{
		std::puts("SoundManager::SetMusicMute: Muting music."); // DEBUG
		StopMusic();
	}
	else if(currentMusicPtr != nullptr)
	{
		std::puts("SoundManager::SetMusicMute: Unmuting music."); // DEBUG
		currentMusicPtr->play();
	}
}

bool SoundManager::IsMusicMuted() const
{
	return musicMuted;
}

void SoundManager::PlaySFX(const sf::SoundBuffer & buffer, const float volume)
{
	assert(volume >= 0.f && volume <= 100.f);
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
