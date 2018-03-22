#include "resourcecache.hpp"

bool ResourceCache::LoadFont(const std::string & file, const std::string & name)
{
	fontStorage[name] = sf::Font();
	if(!fontStorage[name].loadFromFile(file))
	{
		fontStorage.erase(name);
		return false;
	}

	return true;
}

sf::Font * ResourceCache::GetFont(const std::string & name)
{
	if(fontStorage.find(name) == fontStorage.end())
		return nullptr;

	return &(fontStorage[name]);
}
