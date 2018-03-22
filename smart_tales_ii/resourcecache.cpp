#include "resourcecache.hpp"

#include "stringutil.hpp"

ResourceCache & ResourceCache::GetInstance()
{
	static ResourceCache singleton;
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

void ResourceCache::LoadSpriteSheet(const std::string & file)
{
	const std::string name = Util::GetFileName(file);
	sheetStorage[name] = Animation::Sheet();
	sheetStorage[name].LoadFromFile(file);
}

sf::Font & ResourceCache::GetFont(const std::string & name)
{
	auto searchResult = fontStorage.find(name);
	if(searchResult == fontStorage.end())
		throw std::runtime_error("Cannot fetch font resource with name <" + name + ">");

	return searchResult->second;
}

const sf::Texture & ResourceCache::GetTexture(const std::string & name) const
{
	auto searchResult = textureStorage.find(name);
	if(searchResult == textureStorage.end())
		throw std::runtime_error("Cannot fetch texture resource with name <" + name + ">");

	return searchResult->second;
}

sf::Texture & ResourceCache::GetMutableTexture(const std::string & name)
{
	auto searchResult = textureStorage.find(name);
	if(searchResult == textureStorage.end())
		throw std::runtime_error("Cannot fetch mutable texture resource with name <" + name + ">");

	return searchResult->second;
}

const Animation::Sheet & ResourceCache::GetSpriteSheet(const std::string & name) const
{
	auto searchResult = sheetStorage.find(name);
	if(searchResult == sheetStorage.end())
		throw std::runtime_error("Cannot fetch texture resource with name <" + name + ">");

	return searchResult->second;
}
