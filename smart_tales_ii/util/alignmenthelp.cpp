#include "alignmenthelp.hpp"

namespace Util
{
    sf::Vector2i GetRectangleCenter(const sf::IntRect & rect)
    {
        return sf::Vector2i(rect.position.x + (rect.size.x / 2), rect.position.y + (rect.size.y / 2));
    }

    sf::Vector2f GetRectangleCenter(const sf::FloatRect & rect)
    {
        return sf::Vector2f(rect.position.x + (rect.size.x / 2.f), rect.position.y + (rect.size.y / 2.f));
    }

    float GetCenterOffset(const float length, const float center) { return center - (length / 2.f); }

    sf::Vector2f GetCenterOffset(const sf::FloatRect & rect, const sf::Vector2f & center)
    {
        return sf::Vector2f(
            GetCenterOffset(rect.size.x, center.x) + rect.position.x,
            GetCenterOffset(rect.size.y, center.y) + rect.position.y);
    }
}
