#include "resourcecache.hpp"
#include "util/string.hpp"

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

void ResourceCache::LoadMusic(const std::string & file)
{
	const std::string name = Util::GetFileName(file);
	// We need to construct the sf music object in place
	// since it is non copyable and non moveable
	musicStorage.emplace(std::piecewise_construct, std::make_tuple(file), std::make_tuple());
	if(!musicStorage[name].openFromFile(file))
	{
		throw std::runtime_error("Error loading music file: " + file);
	}
}

void ResourceCache::LoadSound(const std::string & file)
{
	const std::string name = Util::GetFileName(file);
	soundBufferStorage.emplace(file, sf::SoundBuffer{});
	if(!soundBufferStorage[name].loadFromFile(file))
	{
		throw std::runtime_error("Error loading sound effects file: " + file);
	}
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

sf::Music & ResourceCache::GetMusic(const std::string & name)
{
	auto searchResult = musicStorage.find(name);
	if(searchResult == musicStorage.end())
		throw std::runtime_error("Cannot fetch music resource with name <" + name + ">");

	return searchResult->second;
}

const sf::SoundBuffer & ResourceCache::GetSoundBuffer(const std::string & name) const
{
	auto searchResult = soundBufferStorage.find(name);
	if(searchResult == soundBufferStorage.end())
		throw std::runtime_error("Cannot fetch music resource with name <" + name + ">");

	return searchResult->second;
}
