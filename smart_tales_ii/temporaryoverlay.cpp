#include "temporaryoverlay.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"

void TemporaryOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void TemporaryOverlay::Setup()
{
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.f);
	text.setPosition(Alignment::GetCenterOffset(text.getLocalBounds(), sf::Vector2f(cWorldWidth / 2.f, 250.f)));
}

void TemporaryOverlay::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	currentTime += elapsed.asSeconds();
	if(currentTime > timeout)
	{
		GameManager::GetInstance().RemoveGamemode(this);
		return;
	}
}

TemporaryOverlay::TemporaryOverlay(const std::string & message, 
	const float timeOutInSeconds)
	: text(message, ResourceCache::GetInstance().GetFont("commodore"), 32),
	timeout(timeOutInSeconds)
{
}
