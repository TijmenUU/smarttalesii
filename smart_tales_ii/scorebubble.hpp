/*
	scorebubble.hpp

	This class is nothing more than a number floating upwards.

	It has a lifetime and velocity defined in its cpp file.
*/

#pragma once
#include <SFML/Graphics.hpp>

#include <string>

class ScoreBubble : public sf::Drawable
{
private:
	sf::Text text;
	float timeAlive = 0.f; // in seconds

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	bool ShouldRemove() const;

	// Return value indicates it is to be removed
	bool Update(const sf::Time & elapsed);

	ScoreBubble(const sf::Vector2f spawnPosition, const unsigned int score);
};