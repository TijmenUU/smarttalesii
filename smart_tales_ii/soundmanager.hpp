#pragma once
#include <array>
#include <SFML/Audio.hpp>

class SoundManager
{
private:
	sf::Music * currentMusicPtr = nullptr, * nextMusicPtr = nullptr;
	bool musicMuted = false;
	float fadeTime = 0.f;
	float fadeInVolumePerSecond = 0.f;
	float fadeOutVolumePerSecond = 0.f;
	float fadeTargetVolume = 100.f;

	std::array<sf::Sound, 32> sounds;
	bool sfxMuted = false;

	void StopAllSounds();
	void InsertSound(const sf::SoundBuffer & buffer, const float volume);

protected:
	friend class GameManager;
	void Update(const sf::Time & elapsed);

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

	SoundManager() = default;
	SoundManager(const SoundManager &) = delete;
	SoundManager(const SoundManager &&) = delete;
	SoundManager & operator = (SoundManager &) = delete;
	SoundManager & operator = (SoundManager &&) = delete;
};
