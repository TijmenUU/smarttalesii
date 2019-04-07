/*
	gameovermessage.hpp

	Utility object used in the ScoreOverlay class

	Defines the catchphrases and information lines in the
	cpp file.

	Each construction gets the next catchphrase / information
	pair until it reaches the last one where it loops around.
*/

#pragma once
#include <SFML/Graphics.hpp>

class GameoverMessage : public sf::Drawable
{
private:
	sf::Text catchPhrase;
	sf::Text information;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	GameoverMessage(const float centerX, const float y);
};
