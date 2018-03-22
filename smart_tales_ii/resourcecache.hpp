#pragma once
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class ResourceCache
{
private:
	std::unordered_map<std::string, sf::Font> fontStorage;
	std::unordered_map<std::string, sf::Texture> textureStorage;

protected:
	friend class Program;
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadFont(const std::string & file);
	// Throws an runtime_error if the file cannot be loaded
	// Uses the filename without extension as name
	void LoadTexture(const std::string & file);

public:
	static ResourceCache & GetInstance();

	sf::Font * GetFont(const std::string & name);
	sf::Texture * GetTexture(const std::string & name);

	ResourceCache() = default;
	ResourceCache(const ResourceCache &) = delete;
	ResourceCache(const ResourceCache &&) = delete;
	ResourceCache & operator = (ResourceCache &) = delete;
	ResourceCache & operator = (ResourceCache &&) = delete;
};
