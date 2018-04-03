#pragma once
#include "resourcecache.hpp"
#include "gamemode.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class GameManager : public sf::Drawable
{
private:
	std::vector<sf::Sound> soundEffects;
	std::vector<std::unique_ptr<Gamemode>> gamemodes;
	sf::Music * currentMusicPtr = nullptr;
	bool musicMuted = false, sfxMuted = false;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
protected:
	friend class Program;

	void Update(const sf::Time & elapsed,
		const Inputhandler & input,
		const sf::View & view);

public:
	static GameManager & GetInstance();
	// Calls Load on gamemode, thus it may throw an runtime_error exception
	void PushGamemode(Gamemode * gamemode);
	bool RemoveGamemode(Gamemode * gamemode);
	void Pop();
	// Inclusive, pops until it finds gamemode, pops that too and then stops
	bool PopUntill(Gamemode * gamemode);
	bool PopAllBelow(Gamemode * gamemode);

	// audio
	void StopMusic();
	void PlayMusic(sf::Music & music);
	float GetMusicVolume() const;
	void SetMusicVolume(const float volume);
	void SetMucicMute(const bool muted);
	bool IsMusicMuted() const;

	void PlaySFX(const sf::SoundBuffer & buffer, const float volume = 100.f);
	void SetSFXMuted(const bool muted);
	bool IsSFXMuted() const;

	GameManager() = default;
	GameManager(const GameManager &) = delete;
	GameManager(const GameManager &&) = delete;
	GameManager & operator = (GameManager &) = delete;
	GameManager & operator = (GameManager &&) = delete;
};
