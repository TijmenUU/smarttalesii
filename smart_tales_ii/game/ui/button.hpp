/*
	button.hpp

	A basic textured button. It has a down and up
	state and works like a toggle button by default.
*/

#pragma once
#include "../animation/animatedsprite.hpp"
#include "../inputhandler.hpp"

class Button : public sf::Drawable
{
private:
	void UpdateButtonVisual();

protected:
	bool isDown;
	bool isEnabled;
	Animation::Sprite buttonSprite;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Returns whether the state changed
	bool Interacts(const Inputhandler & input);

public:
	virtual bool HandleInput(const Inputhandler & input);
	// Update the animated sprite
	virtual void Update(const sf::Time & elapsed);

	bool IsDown() const;
	bool IsEnabled() const;

	virtual bool SetAnimation(const std::string & animation);

	virtual void SetPosition(const sf::Vector2f & position);
	virtual sf::Vector2f GetPosition() const;
	virtual sf::FloatRect GetGlobalbounds() const;

	virtual void Enable();
	virtual void Disable();

	virtual void SetDown(const bool down);

	Button(const Animation::Sheet & buttonSheet,
		const bool enabled = true, 
		const bool down = false);
	virtual ~Button() = default;
};
