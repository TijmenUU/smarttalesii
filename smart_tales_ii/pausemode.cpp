#include "pausemode.hpp"
#include "gamemanager.hpp"

void PauseMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(pauseText, states);
}

bool PauseMode::SurpressUpdate() const
{
	return true;
}

void PauseMode::Load()
{
	sf::Font * fontPtr = fonts.GetFont("commodore");
	if(fontPtr == nullptr)
	{
		throw std::runtime_error("Error fetching commodore font in PausedMode.");
	}

	pauseText.setFont(*fontPtr);
	pauseText.setCharacterSize(32);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setOutlineColor(sf::Color::Black);
	pauseText.setOutlineThickness(2.f);

	auto bounds = pauseText.getGlobalBounds();
	pauseText.setPosition(cWorldWidth / 2.f - bounds.width / 2.f, cWorldHeight / 2.f);
}

void PauseMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(input.WasKeyReleased(sf::Keyboard::P))
	{
		manager.RemoveGamemode(this);
		return;
	}
}

PauseMode::PauseMode(Fonts & fontsRef, GameManager & managerRef, const std::string message)
	:Gamemode(fontsRef, managerRef),
	pauseText()
{
	pauseText.setString(message);
}