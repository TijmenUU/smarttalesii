#include "inputhandler.hpp"
#include <algorithm>

void Inputhandler::ClearState()
{
	keyUpEvents.clear();
	keyDownEvents.clear();
	buttonUpEvents.clear();
	buttonDownEvents.clear();

	textEntered.clear();

	didWindowResize = false;
	cursorMoved = false;
}

void Inputhandler::Update(sf::RenderWindow & window)
{
	ClearState();

	sf::Event event;
	while (window.pollEvent(event))
	{
		//wchar_t input;
		switch (event.type)
		{
			case sf::Event::GainedFocus:
			hasFocus = true;
			break;

			case sf::Event::LostFocus:
			hasFocus = false;
			break;

			case sf::Event::Closed:
			didWindowClose = true;
			break;

			case sf::Event::Resized:
			didWindowResize = true;
			break;

			case sf::Event::TextEntered:
			textEntered += static_cast<char>(event.text.unicode); // may cause issues when out of range (>127)
			break;

			case sf::Event::KeyPressed:
			keyDownEvents.push_back(event.key.code);
			break;

			case sf::Event::KeyReleased:
			keyUpEvents.push_back(event.key.code);
			break;

			case sf::Event::MouseButtonPressed:
			buttonDownEvents.push_back(event.mouseButton.button);
			break;

			case sf::Event::MouseButtonReleased:
			buttonUpEvents.push_back(event.mouseButton.button);
			break;

			case sf::Event::MouseMoved:
			mousePixelPosition = sf::Mouse::getPosition(window);
			cursorMoved = true;
			break;

			case sf::Event::MouseEntered:
			cursorInWindow = true;
			break;

			case sf::Event::MouseLeft:
			cursorInWindow = false;
			break;

			default:
			break;
		}
	}
	// Always refreshing variables:
	mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition); // view might have changed
}

bool Inputhandler::DidWindowResize() const
{
	return didWindowResize;
}

bool Inputhandler::DidWindowClose() const
{
	return didWindowClose;
}

bool Inputhandler::WindowHasFocus() const
{
	return hasFocus;
}

bool Inputhandler::PointingDeviceIsUp() const
{
	return !sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool Inputhandler::PointingDeviceIsDown() const
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool Inputhandler::PointingDevicePressedEvent() const
{
	return std::find(buttonDownEvents.begin(), buttonDownEvents.end(), sf::Mouse::Left) != buttonDownEvents.end();
}
bool Inputhandler::PointingDeviceReleasedEvent() const
{
	return std::find(buttonUpEvents.begin(), buttonUpEvents.end(), sf::Mouse::Left) != buttonUpEvents.end();
}
const sf::Vector2i & Inputhandler::PointingDeviceWindowPosition() const
{
	return mousePixelPosition;
}
const sf::Vector2f & Inputhandler::PointingDeviceWorldPosition() const
{
	return mouseWorldPosition;
}

Inputhandler::Inputhandler()
: keyUpEvents(),
keyDownEvents(),
buttonUpEvents(),
buttonDownEvents(),
textEntered(),
didWindowResize(false),
hasFocus(true),
didWindowClose(false),
cursorInWindow(true),
cursorMoved(false),
mousePixelPosition(0, 0),
mouseWorldPosition(0.f, 0.f)
{
}
