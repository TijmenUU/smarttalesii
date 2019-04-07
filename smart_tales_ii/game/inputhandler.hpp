/*
	inputhandler.hpp

	An utility class that stores all the input related events (and then some)
	to itself every time it's Update function is called. 

	Since the SFML interface already provides a keydown state this class only
	provides events for the mouse and keyboard. On a key release and on a key press,
	but not during a key press. See sf::Keyboard::isKeyPressed for that
*/

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
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
	// Goes through all the recorded events since the last Update call
	// Assumes nothing else called pollEvent on the given window in the mean time!
	// Replaces the current state!
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
