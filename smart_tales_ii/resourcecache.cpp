#include "resourcecache.hpp"

#include "stringutil.hpp"

ResourceCache & ResourceCache::GetInstance()
{
	ResourceCache singleton;
	return singleton;
}

void ResourceCache::LoadFont(const std::string & file)
{
	const std::string name = Util::GetFileName(file);

	fontStorage[name] = sf::Font();
	if(!fontStorage[name].loadFromFile(file))
	{
		throw std::runtime_error("Error loading font <" + file + ">");
	}
}

void ResourceCache::LoadTexture(const std::string & file)
{
	const std::string name = Util::GetFileName(file);
	textureStorage[name] = sf::Texture();
	if(!textureStorage[name].loadFromFile(file))
	{
		throw std::runtime_error("Error loading texture <" + file + ">");
	}
}

sf::Font * ResourceCache::GetFont(const std::string & name)
{
	auto searchResult = fontStorage.find(name);
	if(searchResult == fontStorage.end())
		return nullptr;

	return &(searchResult->second);
}

sf::Texture * ResourceCache::GetTexture(const std::string & name)
{
	auto searchResult = textureStorage.find(name);
	if(searchResult == textureStorage.end())
		return nullptr;

	return &(searchResult->second);
}
