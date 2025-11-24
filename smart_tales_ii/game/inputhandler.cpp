#include "inputhandler.hpp"
#include <SFML/Window/Mouse.hpp>
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

    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::FocusGained>())
        {
            hasFocus = true;
        }

        if(event->is<sf::Event::FocusLost>())
        {
            hasFocus = false;
        }

        if(event->is<sf::Event::Closed>())
        {
            didWindowClose = true;
        }

        if(event->is<sf::Event::Resized>())
        {
            didWindowResize = true;
        }

        if(const auto * textEntered = event->getIf<sf::Event::TextEntered>())
        {
            textEntered += static_cast<char>(textEntered->unicode); // may cause issues when out of range (>127)
        }

        if(const auto * keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            keyDownEvents.push_back(keyPressed->code);
        }

        if(const auto * keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            keyUpEvents.push_back(keyReleased->code);
        }

        if(const auto * buttonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            buttonDownEvents.push_back(buttonPressed->button);
        }

        if(const auto * buttonReleased = event->getIf<sf::Event::MouseButtonReleased>())
        {
            buttonUpEvents.push_back(buttonReleased->button);
        }

        if(event->is<sf::Event::MouseMoved>())
        {
            mousePixelPosition = sf::Mouse::getPosition(window);
            cursorMoved = true;
        }

        if(event->is<sf::Event::MouseEntered>())
        {
            cursorInWindow = true;
        }

        if(event->is<sf::Event::MouseLeft>())
        {
            cursorInWindow = false;
        }
    }
    // Always refreshing variables:
    mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition); // view might have changed
}

bool Inputhandler::DidWindowResize() const { return didWindowResize; }

bool Inputhandler::DidWindowClose() const { return didWindowClose; }

bool Inputhandler::WindowHasFocus() const { return hasFocus; }

bool Inputhandler::PointingDeviceIsUp() const { return !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); }
bool Inputhandler::PointingDeviceIsDown() const { return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); }
bool Inputhandler::PointingDevicePressedEvent() const
{
    return std::find(buttonDownEvents.begin(), buttonDownEvents.end(), sf::Mouse::Button::Left)
        != buttonDownEvents.end();
}
bool Inputhandler::PointingDeviceReleasedEvent() const
{
    return std::find(buttonUpEvents.begin(), buttonUpEvents.end(), sf::Mouse::Button::Left) != buttonUpEvents.end();
}
const sf::Vector2i & Inputhandler::PointingDeviceWindowPosition() const { return mousePixelPosition; }
const sf::Vector2f & Inputhandler::PointingDeviceWorldPosition() const { return mouseWorldPosition; }