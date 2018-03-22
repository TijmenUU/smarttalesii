#pragma once
#include "animatedsprite.hpp"

#include "playerinventory.hpp"

#include <string>

class PlayerSprite : public sf::Drawable
{
private:
	Animation::Sheet upperBodySheet;
	Animation::Sheet legsSheet;

	Animation::Sprite upperBodySprite;
	Animation::Sprite legsSprite;

	bool showingOff = false;
	float showoffTimer = 0.f;

protected:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	bool IsShowingOff() const;
	void ShowOff();

	bool SetAnimation(const std::string & name);
	void SetPosition(const sf::Vector2f & p);

	const sf::Vector2f & GetPosition() const;
	sf::FloatRect GetGlobalBounds() const;

	void Load(const Player::Inventory & inventory);
	void Update(const sf::Time & elapsed);

	PlayerSprite();
};

