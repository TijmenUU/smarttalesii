#pragma once
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>
#include <vector>

struct ResourceCache
{
private:
	std::unordered_map<std::string, sf::Font> fontStorage;

public:
	bool LoadFont(const std::string & file, const std::string & name);

	sf::Font * GetFont(const std::string & name);

	ResourceCache();
};
