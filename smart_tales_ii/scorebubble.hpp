#pragma once
#include <SFML\Graphics.hpp>

#include <string>

class ScoreBubble : public sf::Drawable
{
private:
	sf::Text text;
	float timeAlive; // in seconds

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	bool ShouldRemove() const;

	// Return value indicates it is to be removed
	bool Update(const sf::Time & elapsed);

	ScoreBubble(sf::Font & fontRef, const sf::Vector2f spawnPosition, const unsigned int score);
};