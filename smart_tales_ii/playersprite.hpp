#pragma once
#include "animatedsprite.hpp"

#include <string>

class PlayerSprite : public sf::Drawable
{
private:
	Animation::Sheet upperBodySheet;
	Animation::Sheet legsSheet;

	Animation::Sprite upperBodySprite;
	Animation::Sprite legsSprite;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	bool SetAnimation(const std::string & name);
	void SetPosition(const sf::Vector2f & p);

	const sf::Vector2f & GetPosition() const;
	sf::FloatRect GetGlobalBounds() const;

	void Load();
	void Update(const sf::Time & elapsed);

	PlayerSprite();
};

