#include "obstacles.hpp"

void Obstacle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(obstacleSprite, states);
	
	if(definitionPtr->sensorPurchased)
	{
		target.draw(sensorSprite, states);
	}
}

void Obstacle::Neutralize()
{
	neutralized = true;
	obstacleSprite.SetAnimation("neutralized");
}

bool Obstacle::IsNeutralized() const
{
	return neutralized || definitionPtr->sensorPurchased;
}

bool Obstacle::IsObstacleAnimationFinished() const
{
	return obstacleSprite.IsAnimationFinished();
}

sf::FloatRect Obstacle::GetObstacleGlobalBounds() const
{
	return obstacleSprite.getGlobalBounds();
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
	return obstacleSprite.getPosition() + definitionPtr->neutralizationHintLocalPos;
}

sf::Vector2f Obstacle::GetObstacleCenter() const
{
	auto halfDimensions = obstacleSprite.GetSize() / 2.f;
	return obstacleSprite.getPosition() + halfDimensions;
}

sf::Vector2f Obstacle::GetObstaclePosition() const
{
	return obstacleSprite.getPosition();
}

void Obstacle::SetPosition(const sf::Vector2f & p)
{
	obstacleSprite.setPosition(p);
	sensorSprite.setPosition(p + definitionPtr->sensorLocalPos);
	gesture.SetPosition(definitionPtr->interactionLocalPos + p);
}

bool Obstacle::Update(const sf::Time & elapsed, 
	const float velocity, 
	const Inputhandler & input,
	const sf::FloatRect & playerBounds)
{
	// Input
	bool playerNeutralized = false;
	if(!neutralized)
	{
		const auto swipe = gesture.Update(input);
		if(static_cast<uint8_t>(swipe) & definitionPtr->neutralizationSwipes)
		{
			playerNeutralized = true;
			Neutralize();

			if(GetType() == ObstacleType::Door && swipe == SwipeType::Horizontal_LeftToRight)
			{
				obstacleSprite.FlipHorizontally();
			}
		}
		else if(definitionPtr->sensorPurchased && playerBounds.left + playerBounds.width > sensorSprite.getPosition().x)
		{
			Neutralize();
			sensorSprite.SetAnimation("activated");
		}
	}
	
	// Movement
	const float displacement = elapsed.asSeconds() * velocity;
	const auto newposition = obstacleSprite.getPosition() + sf::Vector2f(displacement, 0.f);
	SetPosition(newposition);

	// Animation
	obstacleSprite.Update(elapsed);
	sensorSprite.Update(elapsed);

	return playerNeutralized;
}

Obstacle::Obstacle(const ObstacleDefinition * definition)
	: definitionPtr(definition),
	obstacleSprite(definition->obstacleSprite),
	sensorSprite(definition->sensorSprite),
	gesture(definition->interactionRadius, sf::Vector2f(0.f, 0.f), definition->minimalDistance),
	neutralized(false)
{
}
