#include "fonts.hpp"

bool Fonts::LoadFont(const std::string & file, const std::string & name)
{
	storage[name] = sf::Font();
	if(!storage[name].loadFromFile(file))
	{
		storage.erase(name);
		return false;
	}

	return true;
}

sf::Font * Fonts::GetFont(const std::string & name)
{
	if(storage.find(name) == storage.end())
		return nullptr;

	return &(storage[name]);
}

Fonts::Fonts()
	:storage()
{
}
