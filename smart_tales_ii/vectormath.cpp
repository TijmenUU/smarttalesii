#include "vectormath.hpp"

#include <cassert>
#include <cmath>
#include <SFML/Graphics/Vertex.hpp>

namespace VectorMathF
{
	float ToDegrees(const float radians)
	{
		return radians * cDegreesPerRad;
	}

	float ToRadians(const float degrees)
	{
		return degrees / cDegreesPerRad;
	}

	float ToRadians(const sf::Vector2f & vec)
	{
		return std::atan2(vec.y, vec.x);
	}

	sf::Vector2f RadiansToVector(const float radians)
	{
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	sf::Vector2f DegreesToVector(const float degrees)
	{
		return RadiansToVector(ToRadians(degrees));
	}

	sf::Vector2f RotateVector(const sf::Vector2f & vec, const float radians)
	{
		float cosRad = std::cos(radians);
		float sinRad = std::sin(radians);
		return sf::Vector2f(vec.x * cosRad - vec.y * sinRad,
			vec.x * sinRad + vec.y * cosRad);
	}

	float Length(const sf::Vector2f & vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	float Distance(const sf::Vector2f & A, const sf::Vector2f & B)
	{
		float x = A.x - B.x; // no std::abs required for squaring
		float y = A.y - B.y; // no std::abs required for squaring
		return std::sqrt(x * x + y * y);
	}

	float Clamp(const float value, const float min, const float max)
	{
		if (value > max)
		{
			return max;
		}

		if (value < min)
		{
			return min;
		}

		return value;
	}

	sf::Vector2f Clamp(const sf::Vector2f & vec,
		const float min,
		const float max)
	{
		return sf::Vector2f(Clamp(vec.x, min, max), Clamp(vec.y, min, max));
	}

	sf::Vector2f ClampLength(sf::Vector2f vec, const float min, const float max)
	{
		float length = Length(vec);
		if (length > max)
		{
			vec *= max / length;
		}
		else if (length < min)
		{
			vec *= min / length;
		}

		return vec;
	}

	sf::Vector2f Normalize(const sf::Vector2f & vec)
	{
		float length = Length(vec);
		return vec / length;
	}

	sf::Vector2f SetLength(const sf::Vector2f & vec, float n)
	{
		float length = Length(vec);
		return vec * n / length;
	}

	float Dot(const sf::Vector2f & A, const sf::Vector2f & B)
	{
		return A.x * B.x + A.y * B.y;
	}

	float Angle(const sf::Vector2f & A, const sf::Vector2f & B)
	{
		return std::acos(Dot(A, B) / (Length(A) * Length(B)));
	}

	sf::Vector2f ScalarProject(const sf::Vector2f & A, const sf::Vector2f & B)
	{
		sf::Vector2f result = Normalize(B); // 1 / length(B)
		result *= Dot(A, result); // (1 / length(B)) * (A . B) == (A . B) / length(B)

		return result;
	}

	bool ClockwiseCompare(const sf::Vector2f & center,
		const sf::Vector2f & a,
		const sf::Vector2f & b)
	{
		if (a.x - center.x >= 0 && b.x - center.x < 0)
			return true;

		if (a.x - center.x < 0 && b.x - center.x >= 0)
			return false;

		if (a.x - center.x == 0 && b.x - center.x == 0)
		{
			if (a.y - center.y >= 0 || b.y - center.y >= 0)
				return a.y > b.y;
			return b.y > a.y;
		}

		// compute the cross product of vectors (center -> a) x (center -> b)
#pragma warning(suppress: 4244) // flooring behaviour of float->int is what we want here
		int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);

		if (det < 0)
		  return true;

		if (det > 0)
		  return false;

		// points a and b are on the same line from the center
		// check which point is closer to the center
#pragma warning(suppress: 4244) // flooring behaviour float -> int is what we want here
		int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
#pragma warning(suppress: 4244) // flooring behaviour float -> int is what we want here
		int d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
		return d1 > d2;
	}
}

namespace VectorMathI
{
	std::int32_t Clamp(const std::int32_t val,
		const std::int32_t min,
		const std::int32_t max)
	{
		if (val > max)
		{
			return max;
		}

		if (val < min)
		{
			return min;
		}

		return val;
	}

	sf::Vector2i Clamp(const sf::Vector2i & vec,
		const std::int32_t min,
		const std::int32_t max)
	{
		return sf::Vector2i(Clamp(vec.x, min, max), Clamp(vec.y, min, max));
	}

	std::int32_t ManhattanDistance(const sf::Vector2i & A,
		const sf::Vector2i & B)
	{
		std::int32_t result = std::abs(A.x - B.x);
		result += std::abs(A.y - B.y);

		return result;
	}

	float Distance(const sf::Vector2i & A, const sf::Vector2i & B)
	{
		std::int32_t x = A.x - B.x; // no std::abs required for squaring
		std::int32_t y = A.y - B.y; // no std::abs required for squaring
		return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y));
	}
}
