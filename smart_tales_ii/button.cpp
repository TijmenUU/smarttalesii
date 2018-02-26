#include "button.hpp"

void Button::UpdateButtonVisual()
{
	if(isDown)
	{
		SetAnimation("down");
	}
	else
	{
		SetAnimation("up");
	}
}

void Button::LoadFromFile(const std::string & animationFile, sf::Texture & textureStorage)
{
	AnimatedSprite::LoadFromFile(animationFile, textureStorage);
	SetAnimation("up");
}

bool Button::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(input.PointingDeviceReleasedEvent())
	{
		const auto inputpos = input.PointingDeviceWorldPosition();
		const auto bounds = getGlobalBounds();
		if(bounds.contains(inputpos))
		{
			isDown = !isDown;
			UpdateButtonVisual();
			return true;
		}
	}

	AnimatedSprite::Update(elapsed);

	return false;
}

bool Button::IsDown() const
{
	return isDown;
}

Button::Button()
	: AnimatedSprite(),
	isDown(false)
{
}
