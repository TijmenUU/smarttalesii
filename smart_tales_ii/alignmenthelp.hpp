/*
	alignmenthelp.hpp

	A simple utility collection for centering AABB shapes or 2D points on
	a given 2D point.

	Beware that in conjunction with sf::Text the boundingbox's left and
	top properties are meant to be used too in centering. So it is best
	to pass in a getLocalBounds() result rather than a getGlobalBounds()
	in case it was already translated before.
*/

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