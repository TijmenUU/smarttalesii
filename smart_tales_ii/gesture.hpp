#pragma once
#include "definitions.hpp"
#include "inputhandler.hpp"

#include <SFML\Graphics.hpp>
#include <vector>

class SwipeGesture
{
protected:
	sf::Vector2f position; // world space position of interaction area center
	float radius, minDist; // in pixels
	bool gestureInProgress;
	sf::Vector2i start; // window space starting coordinate of swipe gesture

public:
	bool IsInProgress() const;

	// Set the center of the interaction area (circle)
	void SetPosition(const sf::Vector2f & newPos);
	// Get the center of the interaction area (circle)
	sf::Vector2f GetPosition() const;

	void SetInteractionRadius(const float newRadius);
	float GetInteractionRadius() const;

	// Returns a swipe gesture upon mouse release
	SwipeType Update(const Inputhandler & input);

	// Resets the current swipe data, but not the position
	void Reset();

	SwipeGesture(const float interactionRadius, 
		const sf::Vector2f & spawnPos,
		const float minimumDistance = 50.f);
};
