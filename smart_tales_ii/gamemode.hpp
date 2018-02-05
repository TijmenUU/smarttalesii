#pragma once
#include "fonts.hpp"
#include "inputhandler.hpp"

#include <SFML\Graphics.hpp>

class Gamemode : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

protected:
	Fonts & fonts;

public:
	virtual void Load() = 0;
	virtual void Update(const sf::Time & elapsed, const Inputhandler & input) = 0;
	virtual void Sleep();
	virtual void Wake();

	Gamemode(Fonts & fontsRef);
};