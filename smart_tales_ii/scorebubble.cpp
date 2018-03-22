#include "scorebubble.hpp"

#include "resourcecache.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>

const float cTimeAliveLimit = 1.5f; // in seconds
const float cVerticalMovementSpeed = 150.f;

void ScoreBubble::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text, states);
}

bool ScoreBubble::ShouldRemove() const
{
	return timeAlive > cTimeAliveLimit;
}

bool ScoreBubble::Update(const sf::Time & elapsed)
{
	const auto elapsedSeconds = elapsed.asSeconds();
	timeAlive += elapsedSeconds;

	auto position = text.getPosition();
	position.y -= cVerticalMovementSpeed * elapsedSeconds;
	text.setPosition(position);

	return ShouldRemove();
}

ScoreBubble::ScoreBubble(const sf::Vector2f spawnPosition, const unsigned int score)
{
	std::stringstream ss;
	ss << '+' << score;

	text.setString(ss.str());
	text.setFont(ResourceCache::GetInstance().GetFont("commodore"));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.f);
	text.setPosition(spawnPosition);
}
