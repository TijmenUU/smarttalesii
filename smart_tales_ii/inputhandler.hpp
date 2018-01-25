#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Inputhandler
{
protected:
	std::vector<sf::Keyboard::Key> keyUpEvents;
	std::vector<sf::Keyboard::Key> keyDownEvents;

	std::vector<sf::Mouse::Button> buttonUpEvents;
	std::vector<sf::Mouse::Button> buttonDownEvents;

	std::string textEntered;
	bool didWindowResize, hasFocus, didWindowClose;
	bool cursorInWindow, cursorMoved;

	sf::Vector2i mousePixelPosition;
	sf::Vector2f mouseWorldPosition;

	void ClearState();
public:
	// goes through all the recorded events since last update
	// assumes nothing else called pollEvent on it in the mean time!
	void Update(sf::RenderWindow & window);

	bool DidWindowResize() const;
	bool DidWindowClose() const;
	bool WindowHasFocus() const;

	// key down event (not iskeydown, initial press only)
	bool WasKeyPressed(const sf::Keyboard::Key k) const;
	// key up event
	bool WasKeyReleased(const sf::Keyboard::Key k) const;

	// button down event (not isButtonPressed, initial press only)
	bool WasButtonPressed(const sf::Mouse::Button b) const;
	// button up event
	bool WasButtonReleased(const sf::Mouse::Button b) const;

	bool IsCursorInWindow() const;
	bool DidCursorMove() const;

	std::string GetTextTyped() const;

	sf::Vector2i GetMouseWindowCoordinate() const;
	sf::Vector2f GetMouseWorldCoordinate() const;

	Inputhandler();
};
