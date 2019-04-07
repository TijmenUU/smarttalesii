#include "../../util/alignmenthelp.hpp"
#include "../gamemanager.hpp"
#include "temporaryoverlay.hpp"

void TemporaryOverlay::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void TemporaryOverlay::Setup()
{
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.f);
	text.setPosition(Util::GetCenterOffset(text.getLocalBounds(), sf::Vector2f(cWorldWidth / 2.f, 250.f)));
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
	: text(message, ResourceCache::GetInstance().GetFont("commodore"), 38),
	timeout(timeOutInSeconds)
{
}
