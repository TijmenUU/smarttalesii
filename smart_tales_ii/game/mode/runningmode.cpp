#include "../../util/alignmenthelp.hpp"
#include "../../util/vectormath.hpp"
#include "../gamemanager.hpp"
#include "../overlay/uioverlay.hpp"
#include "../overlay/scoreoverlay.hpp"
#include "../overlay/winoverlay.hpp"
#include "../resourcecache.hpp"
#include <array>
#include <iomanip>
#include <memory>
#include "runningmode.hpp"
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

void RunningMode::GameOver(const Obstacle::Type cause)
{
	auto & manager = GameManager::GetInstance();
	manager.Pop(); // delete our created overlay
	manager.PushGamemode(std::make_unique<ScoreOverlay>(score, playerInventory, cause));
	return;
}

void RunningMode::Reset()
{
	background.Reset();

	obstacles.clear();
	obstacleSpawner.Reset();
	
	runningtimeMs = 0U;
	scrollVelocity = gameDifficulty.GetScrollVelocity(playerInventory.GetSensorUpgradeCount(), 0.f);

	score.Reset();
	scoreBubbles.clear();
}

bool RunningMode::SuppressDraw() const
{
	return true;
}

bool RunningMode::SuppressUpdate() const
{
	return true;
}

void RunningMode::OnEnter()
{
	Reset();
	auto & music = ResourceCache::GetInstance().GetMusic("pixelland");
	music.setVolume(100);
	music.setLoop(true);
	SoundManager::GetInstance().CrossFadeMusic(music);
}

bool RunningMode::UpdateObstacles(const sf::Time & elapsed, const Inputhandler & input)
{
	const auto playerBounds = player.GetGlobalBounds();
	const float displacement = elapsed.asSeconds() * -scrollVelocity;

	auto iter = obstacles.begin();
	while(iter != obstacles.end())
	{
		auto & obstacle = *(*iter); // beautiful double deref

		if(obstacle.CanDespawn())
		{
			iter = obstacles.erase(iter);
			continue; // make sure we cannot use the deleted obj anymore
		}

		const auto updateResult = obstacle.Update(elapsed, input, displacement, playerBounds);
		switch(updateResult)
		{
			case Obstacle::UpdateResult::PlayerKilled:
			GameOver(obstacle.GetType());
			return true;

			case Obstacle::UpdateResult::ObstacleNeutralizedByPlayer:
			{
				const auto obstacleCenter = obstacle.GetNeutralizationPosition();
				const float playerObstacleDist = VectorMathF::Distance(obstacleCenter, player.GetPosition());

				const auto currencyScore = score.GetNeutralizationCurrency(playerObstacleDist);
				// spawn score bubble
				scoreBubbles.emplace_back(input.PointingDeviceWorldPosition(), currencyScore);
				currencyDisplay.SetValue(score.GetTotalCurrency() + playerInventory.GetCurrency());
			}
			break;

			case Obstacle::UpdateResult::ObstacleNeutralizedBySensor:
			if(obstacle.GetType() == Obstacle::Type::Phone)
			{
				player.ShowOff();
			}
			break;

			default:
			break;
		}

		// Advance the iterator
		++iter;
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
					obstacleHintText.setPosition(Util::GetCenterOffset(obstacleHintText.getLocalBounds(), hintPosition));

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

		if(scoreBubbles[i].Update(elapsed))
		{

			scoreBubbles.erase(scoreBubbles.begin() + i);
		}
	}
}

void RunningMode::Setup()
{
	auto & manager = GameManager::GetInstance();
	manager.PopAllBelow(this);

	obstacleSpawner.Load(playerInventory, cWorldWidth, cFloorY);

	gameDifficulty.LoadFromFile(cGameDifficultyFile);//GetDifficulty(cGameDifficultyFile);
	
	const auto playerBounds = player.GetGlobalBounds();
	player.SetPosition(sf::Vector2f(playerBounds.width, cFloorY - playerBounds.height));

	sf::Font & font = ResourceCache::GetInstance().GetFont("commodore");
	obstacleHintText.setFont(font);
	obstacleHintText.setCharacterSize(26);
	obstacleHintText.setFillColor(sf::Color::White);
	obstacleHintText.setOutlineColor(sf::Color::Black);
	obstacleHintText.setOutlineThickness(2.f);

	currencyDisplay.CenterOn(cWorldWidth / 2.f, 25.f);

	if(playerInventory.GetSensorUpgradeCount() > 3)
	{
		manager.PushGamemode(std::make_unique<WinOverlay>());
	}
	else
	{
		manager.PushGamemode(std::make_unique<UIOverlay>());
	}
}

void RunningMode::Update(const sf::Time & elapsed, const Inputhandler & input)
{
	if(GameManager::GetInstance().GetDebugFlag())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			GameOver(Obstacle::Type::Unknown);
			return;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			scrollVelocity *= 0.95f;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			scrollVelocity *= 1.05f;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			auto & manager = GameManager::GetInstance();
			manager.PopAllBelow(nullptr);
			manager.PushGamemode(std::make_unique<WinOverlay>(0.f));
			return;
		}
	}

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
	scrollVelocity = gameDifficulty.GetScrollVelocity(playerInventory.GetSensorUpgradeCount(),
		sf::milliseconds(runningtimeMs).asSeconds());

	runningtimeMs += elapsed.asMilliseconds();
	obstacleSpawner.Update(elapsed, obstacles, cWorldWidth);
}

RunningMode::RunningMode(const Player::Inventory & inventory)
	: background(cWorldWidth),
	currencyDisplay(5U, "", inventory.GetCurrency()),
	player(inventory),
	playerInventory(inventory)
{

}
