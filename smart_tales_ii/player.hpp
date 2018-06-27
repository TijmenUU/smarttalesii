#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player : public sf::Sprite
{
protected:
	sf::Texture texture;

public:
	// May throw std::runtime_error if texture cannot be loaded
	void Load(const std::string & textureSrc);

	Player();
};

