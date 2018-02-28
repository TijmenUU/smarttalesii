#include "button.hpp"

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(buttonSprite, states);
}

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

void Button::LoadFromFile(const std::string & animationFile, sf::Texture & textureStorage)
{
	buttonSprite.LoadFromFile(animationFile, textureStorage);
	UpdateButtonVisual();
}

bool Button::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(input.PointingDeviceReleasedEvent() && isEnabled)
	{
		const auto inputpos = input.PointingDeviceWorldPosition();
		const auto bounds = buttonSprite.getGlobalBounds();
		if(bounds.contains(inputpos))
		{
			isDown = !isDown;
			UpdateButtonVisual();
			return true;
		}
	}

	buttonSprite.Update(elapsed);

	return false;
}

bool Button::IsDown() const
{
	return isDown;
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

Button::Button(const bool enabled, const bool down)
	: isDown(down),
	isEnabled(enabled),
	buttonSprite()
{
}
