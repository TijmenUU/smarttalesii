#include "obstacles.hpp"

void Obstacle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	target.draw(debugShape, states); // debug
}

bool Obstacle::IsNeutralized() const
{
	return neutralized;
}

sf::Vector2f Obstacle::GetSize() const
{
	const auto bounds = sprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

sf::Vector2f Obstacle::GetCenter() const
{
	const auto position = sprite.getPosition();
	const auto bounds = sprite.getGlobalBounds();
	return sf::Vector2f(position.x + (bounds.width / 2.f), position.y + (bounds.height /2.f));
}

sf::Vector2f Obstacle::GetPosition() const
{
	return sprite.getPosition();
}

void Obstacle::SetNeutralized(const bool value)
{
	neutralized = value;
}

void Obstacle::SetPosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
	// gesture.SetPosition(GetCenter());
	// start debug
	const auto centerpos = GetCenter();
	gesture.SetPosition(centerpos);
	const auto radius = debugShape.getRadius();
	debugShape.setPosition(centerpos - sf::Vector2f(radius, radius));
	// end debug
}

// Possibly use custom bounding box, current is sprite bounding box
bool Obstacle::CollidesWith(const sf::FloatRect & other) const
{
	if(neutralized)
	{
		return false;
	}
	
	return other.intersects(sprite.getGlobalBounds());
}

bool Obstacle::Update(const sf::Time & elapsed, const float velocity, const Inputhandler & input)
{
	// Input
	if(!neutralized)
	{
		const auto swipeInfo = static_cast<uint8_t>(gesture.Update(input));
		if(swipeInfo & gestureNeutralizeFlag)
		{
			neutralized = true;
		}

		// start debug
		debugShape.setOutlineColor(swipeInfo == 0 ? sf::Color::Red : sf::Color::Green);
		// end debug
	}
	
	// Movement
	const float displacement = elapsed.asSeconds() * velocity;
	const auto newposition = sprite.getPosition() + sf::Vector2f(displacement, 0.f);
	SetPosition(newposition);

	return neutralized;
}

Obstacle::Obstacle(const Definition::Obstacle & obstacleDefinition, const sf::Vector2f & spawnPosition)
	: sprite(obstacleDefinition.texture),
	debugShape(obstacleDefinition.interactionRadius), // debug
	gestureNeutralizeFlag(obstacleDefinition.neutralizationSwipes),
	gesture(obstacleDefinition.interactionRadius, spawnPosition, obstacleDefinition.minimalDistance),
	type(obstacleDefinition.type),
	neutralized(false)
{
	sprite.setPosition(spawnPosition);

	// start debug
	debugShape.setFillColor(sf::Color::Transparent);
	debugShape.setOutlineColor(sf::Color::Red);
	debugShape.setOutlineThickness(1.f);
	// end debug
}
