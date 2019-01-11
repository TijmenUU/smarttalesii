/*
	soundmanager.hpp

	A class that provides a single interface for playing sounds
	and music throughout this application. 
	
	Use the SoundManager::GetInstance() instead of constructing
	one yourself.

	Don't forget to Update it in case of using the crossfade
	functionality. (GameManager class is defined as friend here)
*/

#pragma once
#include <array>
#include <SFML/Audio.hpp>

class SoundManager
{
private:
	sf::Music * currentMusicPtr, * nextMusicPtr;
	
	bool musicMuted;
	bool sfxMuted;
	
	float fadeTime;
	float currentFadeTime;
	float fadeInVolumePerSecond;
	float fadeOutVolumePerSecond;

	std::array<sf::Sound, 32> sounds;

protected:
	friend class GameManager;
	
	void StopAllSounds();
	void InsertSound(const sf::SoundBuffer & buffer, const float volume);
	void Update(const sf::Time & elapsed);

	SoundManager();

public:
	static SoundManager & GetInstance();

	void StopMusic();
	void PlayMusic(sf::Music & music);
	void CrossFadeMusic(sf::Music & next, const float time = 0.5f);
	float GetMusicVolume() const;
	void SetMusicVolume(const float volume);
	void SetMusicMute(const bool muted);
	bool IsMusicMuted() const;

	void PlaySFX(const sf::SoundBuffer & buffer, const float volume = 100.f);
	void SetSFXMute(const bool muted);
	bool IsSFXMuted() const;

	SoundManager(const SoundManager &) = delete;
	SoundManager(const SoundManager &&) = delete;
	SoundManager & operator = (SoundManager &) = delete;
	SoundManager & operator = (SoundManager &&) = delete;
};
