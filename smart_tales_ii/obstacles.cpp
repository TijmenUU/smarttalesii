#include "obstacles.hpp"

bool Obstacle::IsNeutralized() const
{
	return neutralized;
}

ObstacleType Obstacle::GetType() const
{
	return definitionPtr->type;
}

const std::string & Obstacle::GetNeutralizationHint() const
{
	return definitionPtr->neutralizationHint;
}

sf::Vector2f Obstacle::GetNeutralizationHintPosition() const
{
	return getPosition() + definitionPtr->neutralizationHintLocalPos;
}

bool Obstacle::Update(const sf::Time & elapsed, const float velocity, const Inputhandler & input)
{
	// Input
	if(!neutralized)
	{
		const auto swipe = gesture.Update(input);
		if(static_cast<uint8_t>(swipe) & definitionPtr->neutralizationSwipes)
		{
			neutralized = true;
			SetAnimation("neutralized");
			if(GetType() == ObstacleType::Door && swipe == SwipeType::Horizontal_LeftToRight)
			{
				FlipHorizontally();
				// compensate for flip 
				auto position = getPosition();
				position.x += getGlobalBounds().width;
				setPosition(position);
			}
		}
	}
	
	// Movement
	const float displacement = elapsed.asSeconds() * velocity;
	const auto newposition = getPosition() + sf::Vector2f(displacement, 0.f);
	setPosition(newposition);
	gesture.SetPosition(definitionPtr->interactionLocalPos + newposition);

	// Animation
	AnimatedSprite::Update(elapsed);

	return neutralized;
}

Obstacle::Obstacle(const ObstacleDefinition * definition)
	: AnimatedSprite(definition->animatedSprite),
	definitionPtr(definition),
	gesture(definition->interactionRadius, sf::Vector2f(0.f, 0.f), definition->minimalDistance),
	neutralized(false)
{
}
