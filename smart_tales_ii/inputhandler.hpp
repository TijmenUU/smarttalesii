#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Inputhandler
{
private:
	std::vector<sf::Keyboard::Key> keyUpEvents;
	std::vector<sf::Keyboard::Key> keyDownEvents;

	std::vector<sf::Mouse::Button> buttonUpEvents;
	std::vector<sf::Mouse::Button> buttonDownEvents;

	std::string textEntered;
	bool didWindowResize = false, hasFocus = true, didWindowClose = false;
	bool cursorInWindow = true, cursorMoved = false;

	sf::Vector2i mousePixelPosition = sf::Vector2i(0, 0);
	sf::Vector2f mouseWorldPosition = sf::Vector2f(0.f, 0.f);

	void ClearState();
public:
	// goes through all the recorded events since last update
	// assumes nothing else called pollEvent on it in the mean time!
	void Update(sf::RenderWindow & window);

	bool DidWindowResize() const;
	bool DidWindowClose() const;
	bool WindowHasFocus() const;

	/* Main input methods */
	// is it currently released
	bool PointingDeviceIsUp() const;
	// is it currently being pressed down
	bool PointingDeviceIsDown() const;
	// did it just get pressed
	bool PointingDevicePressedEvent() const;
	// did it just get released
	bool PointingDeviceReleasedEvent() const;
	const sf::Vector2i & PointingDeviceWindowPosition() const;
	const sf::Vector2f & PointingDeviceWorldPosition() const;
};
