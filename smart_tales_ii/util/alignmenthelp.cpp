#include "alignmenthelp.hpp"

namespace Util
{
	sf::Vector2i GetRectangleCenter(const sf::IntRect & rect)
	{
		return sf::Vector2i(rect.left + (rect.width / 2), rect.top + (rect.height / 2));
	}

	sf::Vector2f GetRectangleCenter(const sf::FloatRect & rect)
	{
		return sf::Vector2f(rect.left + (rect.width / 2.f), rect.top + (rect.height / 2.f));
	}

	float GetCenterOffset(const float length, const float center)
	{
		return center - (length / 2.f);
	}

	sf::Vector2f GetCenterOffset(const sf::FloatRect & rect, const sf::Vector2f & center)
	{
		return sf::Vector2f(GetCenterOffset(rect.width, center.x) + rect.left,
			GetCenterOffset(rect.height, center.y) + rect.top);
	}
}
