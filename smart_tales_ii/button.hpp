#pragma once
#include "animatedsprite.hpp"
#include "inputhandler.hpp"

class Button : public AnimatedSprite
{
private:
	bool isDown;

	void UpdateButtonVisual();

public:
	void LoadFromFile(const std::string & animationFile, sf::Texture & textureStorage) override;
	// return value indicates change of button state (gone pressed or gone up == true)
	bool Update(const sf::Time & elapsed, const Inputhandler & input);

	bool IsDown() const;

	Button();
};
