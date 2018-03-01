#pragma once
#include "animatedsprite.hpp"
#include "inputhandler.hpp"

class Button : public sf::Drawable
{
protected:
	bool isDown;
	bool isEnabled;
	AnimatedSprite buttonSprite;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void UpdateButtonVisual();

public:
	virtual void LoadFromFile(const std::string & animationFile, sf::Texture & textureStorage);
	// return value indicates change of button state (gone pressed or gone up == true)
	virtual bool Update(const sf::Time & elapsed, const Inputhandler & input);

	virtual bool IsDown() const;

	virtual bool SetAnimation(const std::string & animation);

	virtual void SetPosition(const sf::Vector2f & position);
	virtual sf::Vector2f GetPosition() const;
	virtual sf::FloatRect GetGlobalbounds() const;

	virtual void Enable();
	virtual void Disable();

	virtual void SetDown(const bool down);

	Button(const bool enabled = true, const bool down = false);
	virtual ~Button() = default;
};
