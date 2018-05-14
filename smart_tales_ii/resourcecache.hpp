/*
	resourcecache.hpp

	A very simple and naive implementation of a resource cache
	that allows the requesting of assets by string keys. The
	cache uses unordered_maps so repeated fetches may be slow.

	It is expected to be loaded once and then used. Pointers
	will remain valid after a load, but iterators are invalidated.

	Don't use the constructor, use ResourceCache::GetInstance()
*/

#pragma once
#include "animationsheet.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class ResourceCache
{
private:
	std::unordered_map<std::string, sf::Font> fontStorage;
	std::unordered_map<std::string, sf::Texture> textureStorage;
	std::unordered_map<std::string, Animation::Sheet> sheetStorage;
	std::unordered_map<std::string, sf::Music> musicStorage;
	std::unordered_map<std::string, sf::SoundBuffer> soundBufferStorage;

protected:
	friend class Program;
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadFont(const std::string & file);
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadTexture(const std::string & file);
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadSpriteSheet(const std::string & file);
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadMusic(const std::string & file);
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadSound(const std::string & file);

public:
	static ResourceCache & GetInstance();

	sf::Font & GetFont(const std::string & name);
	const sf::Texture & GetTexture(const std::string & name) const;
	// Dangerous, use GetTexture() instead
	sf::Texture & GetMutableTexture(const std::string & name);
	const Animation::Sheet & GetSpriteSheet(const std::string & name) const;
	sf::Music & GetMusic(const std::string & name);
	const sf::SoundBuffer & GetSoundBuffer(const std::string & name) const;

	ResourceCache() = default;
	ResourceCache(const ResourceCache &) = delete;
	ResourceCache(const ResourceCache &&) = delete;
	ResourceCache & operator = (ResourceCache &) = delete;
	ResourceCache & operator = (ResourceCache &&) = delete;
};
