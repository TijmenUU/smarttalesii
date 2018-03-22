#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

/*
	Utility tools for alignment of GUI
*/

namespace Alignment
{
	sf::Vector2i GetRectangleCenter(const sf::IntRect & rect);

	sf::Vector2f GetRectangleCenter(const sf::FloatRect & rect);

	float GetCenterOffset(const float length, const float center);

	sf::Vector2f GetCenterOffset(const sf::FloatRect & rect, const sf::Vector2f & center);
}