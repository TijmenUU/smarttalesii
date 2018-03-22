#include "button.hpp"

void Button::UpdateButtonVisual()
{
	if(isDown)
	{
		buttonSprite.SetAnimation("down");
	}
	else
	{
		buttonSprite.SetAnimation("up");
	}
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(buttonSprite, states);
}

bool Button::Interacts(const Inputhandler & input)
{
	if(input.PointingDeviceReleasedEvent() && isEnabled)
	{
		const auto inputpos = input.PointingDeviceWorldPosition();
		const auto bounds = buttonSprite.getGlobalBounds();
		if(bounds.contains(inputpos))
		{
			isDown = !isDown;
			return true;
		}
	}

	return false;
}

bool Button::HandleInput(const Inputhandler & input)
{
	if(isEnabled && Interacts(input))
	{
		UpdateButtonVisual();
		return true;
	}

	return false;
}

void Button::Update(const sf::Time & elapsed)
{
	buttonSprite.Update(elapsed);
}

bool Button::IsDown() const
{
	return isDown;
}

bool Button::IsEnabled() const
{
	return isEnabled;
}

bool Button::SetAnimation(const std::string & animation)
{
	return buttonSprite.SetAnimation(animation);
}

void Button::SetPosition(const sf::Vector2f & position)
{
	buttonSprite.setPosition(position);
}

sf::Vector2f Button::GetPosition() const
{
	return buttonSprite.getPosition();
}

sf::FloatRect Button::GetGlobalbounds() const
{
	return buttonSprite.getGlobalBounds();
}

void Button::Enable()
{
	isEnabled = true;
}

void Button::Disable()
{
	isEnabled = false;
}

void Button::SetDown(const bool down)
{
	isDown = down;
	UpdateButtonVisual();
}

Button::Button(const Animation::Sheet & buttonSheet, 
	const bool enabled, 
	const bool down)
	: isDown(down),
	isEnabled(enabled),
	buttonSprite(buttonSheet)
{
	UpdateButtonVisual();
}
