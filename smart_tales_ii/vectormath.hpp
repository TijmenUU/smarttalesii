/*
	vectormath.hpp

	Utility functions that take a float vector (namespace VectorMathF)
	or an integer vector (namespace VectorMathI)
*/

#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>

namespace VectorMathF
{
	const float PI = 3.1415927f;
	const float cDegreesPerRad = 57.2958f;
	// Offset angle used when converting from radians to degrees
	const float cAngleOffsetSFML = 90.f;

	// Convert radians to degrees
	float ToDegrees(const float radians);

	// Convert degrees to radians
	// Keep in mind SFML has a 90 degree offset!
	float ToRadians(const float degrees);

	// Gets the angle with the X axis
	float ToRadians(const sf::Vector2f & vec);

	// Helper function to turn an angle into a normalized 2D vector
	sf::Vector2f RadiansToVector(const float radians);

	// Helper function to turn an angle into a normalized 2D vector
	sf::Vector2f DegreesToVector(const float degrees);

	sf::Vector2f RotateVector(const sf::Vector2f & vec, const float radians);

	// Returns the length of the vector
	float Length(const sf::Vector2f & vec);

	float Distance(const sf::Vector2f & A, const sf::Vector2f & B);

	// Clamps value to [-range, range]
	float Clamp(const float value, const float min, const float max);

	// Per component clamping
	sf::Vector2f Clamp(const sf::Vector2f & vec,
		const float min,
		const float max);

	// Limits the length of the vector to given values
	// range is minLength to maxLength
	sf::Vector2f ClampLength(sf::Vector2f vec, const float min, const float max);

	// Sets the length of the vector to 1
	sf::Vector2f Normalize(const sf::Vector2f & vec);

	// Sets the length of the vector to n
	sf::Vector2f SetLength(const sf::Vector2f & vec, float n);

	// Good analogy is energy absorded. Dot product in a way
	// signifies the ammount of overlap of two vectors and how
	// much they strengthen each other (can be negative or zero!)
	float Dot(const sf::Vector2f & A, const sf::Vector2f & B);

	// In radians, angle between vector A and B
	float Angle(const sf::Vector2f & A, const sf::Vector2f & B);

	// Returns vector A projected on vector B (A as component of vector B)
	// => Soh Cah Toa
	sf::Vector2f ScalarProject(const sf::Vector2f & A, const sf::Vector2f & B);

	// Sorting function to order a list of vectors clockwise
	bool ClockwiseCompare(const sf::Vector2f & center,
		const sf::Vector2f & a,
		const sf::Vector2f & b);
}

// Contains a small subset of functions that make sense for
// integer math. Check out the float namespace for more.
namespace VectorMathI
{
	// Clamp val to [-range, range]
	std::int32_t Clamp(const std::int32_t val,
		const std::int32_t min,
		const std::int32_t max);

	// Clamp vec.x & vec.y to [-range, range]
	sf::Vector2i Clamp(const sf::Vector2i & vec,
		const std::int32_t min,
		const std::int32_t max);

	std::int32_t ManhattanDistance(const sf::Vector2i & A,
		const sf::Vector2i & B);

	float Distance(const sf::Vector2i & A, const sf::Vector2i & B);
}
