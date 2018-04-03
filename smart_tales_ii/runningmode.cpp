#include "runningmode.hpp"

#include "alignmenthelp.hpp"
#include "gamemanager.hpp"
#include "uioverlay.hpp"
#include "resourcecache.hpp"
#include "scoremode.hpp"
#include "vectormath.hpp"
#include "winoverlay.hpp"

// Obstacles
#include "furnitureobstacle.hpp"
#include "doorobstacle.hpp"
#include "lightobstacle.hpp"
#include "phoneobstacle.hpp"

#include <array>
#include <iomanip>
#include <memory>
#include <sstream>

// Config files
const std::string cGameDifficultyFile = "difficulty.txt";

// Utility consts
const float cFloorY = 520.f; // in pixels

void RunningMode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);

	for(size_t i = 0; i < obstacles.size(); ++i)
	{
		target.draw(*(obstacles[i]), states);
	}

	for(size_t i = 0; i < scoreBubbles.size(); ++i)
	{
		target.draw(scoreBubbles[i], states);
	}

	target.draw(player, states);

	target.draw(currencyDisplay, states);

	if(drawObstacleHint)
		target.draw(obstacleHintText, states);
}

void RunningMode::SpawnObstacle()
{
	currentTimeout = 0;

	if(obstacleSpawnIndex >= obstacleFactory.size())
	{
		obstacleSpawnIndex = 0;
	}

	auto * copy = obstacleFactory[obstacleSpawnIndex]->Clone();
	obstacles.emplace_back(copy);
	
	++obstacleSpawnIndex;
}

void RunningMode::SpawnScoreBubble(const sf::Vector2f & mousePos, const unsigned int score)
{
	scoreBubbles.emplace_back(mousePos, score);
}

void RunningMode::GameOver(const Obstacle::Type cause)
{
	auto & manager = GameManager::GetInstance();
	manager.Pop(); // delete our created overlay
	manager.PushGamemode(new ScoreMode(score, playerInventory, Obstacle::GetGameOverString(cause)));
	return;
}

void RunningMode::Reset()
{
	background.Reset();

	obstacles.clear();

	obstacleSpawnIndex = 0;
	currentTimeout = 0.f;
	// TODO tweak this initial scroll velocity expression
	scrollVelocity = gameDifficulty.GetStartScrollVelocity() + playerInventory.GetSensorUpgradeCount() * 25.f;

	score.Reset();
	scoreBubbles.clear();
}

bool RunningMode::SurpressDraw() const
{
	return true;
}

bool RunningMode::SurpressUpdate() const
{
	return true;
}

void RunningMode::OnEnter()
{
	Reset();
	auto & music = ResourceCache::GetInstance().GetMusic("pixelland");
	music.setVolume(100);
	music.setLoop(true);
	GameManager::GetInstance().PlayMusic(music);
}

bool RunningMode::UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input)
{
	const auto playerBounds = player.GetGlobalBounds();
	const float displacement = elapsed.asSeconds() * -scrollVelocity;

	for(int64_t i = static_cast<int64_t>(obstacles.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // negative indexes should never occur
		auto & obstacle = *(obstacles[i]);

		if(obstacle.CanDespawn())
		{
#pragma warning(suppress: 4244) // obstacle vector size should never exceed precision of int64_t
			obstacles.erase(obstacles.begin() + i);
			continue; // make sure we cannot use the deleted obj anymore
		}

		const auto wasNeutralized = obstacle.IsNeutralizedByPlayer();
		obstacle.Update(elapsed, input, displacement, playerBounds);
		
		if(wasNeutralized != obstacle.IsNeutralizedByPlayer())
		{
			const auto obstacleCenter = obstacle.GetNeutralizationPosition();
			const float playerObstacleDist = VectorMathF::Distance(obstacleCenter, player.GetPosition());
			
			const auto currencyScore = score.GetNeutralizationCurrency(playerObstacleDist);
			SpawnScoreBubble(input.PointingDeviceWorldPosition(), currencyScore);
			currencyDisplay.SetValue(score.GetTotalCurrency());
		}
		else if(obstacle.GetKillBounds().intersects(playerBounds))
		{
			if(!obstacle.IsUnharmful())
			{
				GameOver(obstacle.GetType());

				return true;
			}
			else if(obstacle.GetType() == Obstacle::Type::Phone && 
				!player.IsShowingOff() && 
				obstacle.IsActive())
			{
				player.ShowOff();
			}	
		}
	}

	return false;
}

void RunningMode::UpdateHints()
{
	drawObstacleHint = false;
	if(obstacles.size() > 0U)
	{
		for(size_t i = 0; i < obstacles.size(); ++i)
		{
			const auto & obstacle = *(obstacles[i]);
			if(!obstacle.IsUnharmful())
			{
				auto obstaclePosition = obstacle.GetNeutralizationPosition();
				if(obstaclePosition.x <= gameDifficulty.GetHintBorderXCoord())
				{
					obstacleHintText.setString(Obstacle::GetHintString(obstacle.GetType()));
					const auto hintPosition = obstacle.GetHintPosition();
					obstacleHintText.setPosition(Alignment::GetCenterOffset(obstacleHintText.getLocalBounds(), hintPosition));

					drawObstacleHint = true;
					break;
				}
			}
		}
	}
}

void RunningMode::UpdateScoreBubbles(const sf::Time & elapsed)
{
	for(int64_t i = static_cast<int64_t>(scoreBubbles.size()) - 1; i >= 0; --i)
	{
#pragma warning(suppress: 4244) // scoreBubbles vector size should never exceed precision of int64_t
		if(scoreBubbles[i].Update(elapsed))
		{
#pragma warning(suppress: 4244) // scoreBubbles vector size should never exceed precision of int64_t
			scoreBubbles.erase(scoreBubbles.begin() + i);
		}
	}
}

void RunningMode::Setup()
{
	auto & manager = GameManager::GetInstance();
	manager.PopAllBelow(this);

	auto & cache = ResourceCache::GetInstance();
	obstacleFactory.emplace_back(new Obstacle::Furniture(playerInventory.HasObstacleCounter(Obstacle::Type::Furniture)));	
	obstacleFactory.emplace_back(new Obstacle::Door(playerInventory.HasObstacleCounter(Obstacle::Type::Door)));
	obstacleFactory.emplace_back(new Obstacle::Light(playerInventory.HasObstacleCounter(Obstacle::Type::Light)));	
	obstacleFactory.emplace_back(new Obstacle::Phone(playerInventory.HasObstacleCounter(Obstacle::Type::Phone)));

	for(size_t i = 0; i < obstacleFactory.size(); ++i)
	{
		obstacleFactory[i]->SetPosition(sf::Vector2f(0.f, 0.f));
#pragma warning(suppress: 4244) // conversion from float to int should not be a problem for resolutions
		obstacleFactory[i]->SetSpawnPosition(cWorldWidth, cFloorY);
	}

	gameDifficulty.LoadFromFile(cGameDifficultyFile);//GetDifficulty(cGameDifficultyFile);
	
	const auto playerBounds = player.GetGlobalBounds();
	player.SetPosition(sf::Vector2f(playerBounds.width, cFloorY - playerBounds.height));

	sf::Font & font = cache.GetFont("commodore");
	obstacleHintText.setFont(font);
	obstacleHintText.setCharacterSize(26);
	obstacleHintText.setFillColor(sf::Color::White);
	obstacleHintText.setOutlineColor(sf::Color::Black);
	obstacleHintText.setOutlineThickness(2.f);

	currencyDisplay.CenterOn(cWorldWidth / 2.f, 25.f);

	if(playerInventory.GetSensorUpgradeCount() > 3)
	{
		manager.PushGamemode(new WinOverlay());
	}
	else
	{
		manager.PushGamemode(new UIOverlay());
	}
}

void RunningMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	// debug
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		GameOver(Obstacle::Type::Unknown);
		return;
	}
	// end debug
	background.Update(elapsed, -scrollVelocity);

	UpdateScoreBubbles(elapsed);

	if(UpdateObstacles(elapsed, input))
		return;

	player.Update(elapsed);

	UpdateHints();

	const auto elapsedSeconds = elapsed.asSeconds();

	score.distance += elapsedSeconds * scrollVelocity;

	currencyDisplay.Update(elapsed);

	// Anything affected by the scrolling velocity should be updated BEFORE this line
	scrollVelocity += gameDifficulty.GetScrollIncrementVelocity() * elapsedSeconds;
	if(scrollVelocity > gameDifficulty.GetMaxScrollVelocity())
	{
		scrollVelocity = gameDifficulty.GetMaxScrollVelocity();
	}

	// TODO add better spawn algorithm
	currentTimeout += elapsedSeconds;
	if(obstacles.size() == 0)
	{
		SpawnObstacle();
	}
	else
	{
		const auto obstacleBounds = obstacles.back()->GetKillBounds();
		if(currentTimeout > spawnTimeout && obstacleBounds.width + obstacleBounds.left < cWorldWidth)
		{
			SpawnObstacle();
		}
	}
}

RunningMode::RunningMode(const Player::Inventory & inventory)
	: background(cWorldWidth),
	currencyDisplay(5U, "score "),
	player(inventory),
	playerInventory(inventory)
{

}
