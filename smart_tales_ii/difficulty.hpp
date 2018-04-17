#pragma once
#include <string>

class Difficulty
{
private:
	float startVelocity = 0.f;	// pixels per second
	float velocityControl = 0.f;
	float maxVelocity = 0.f; // pixels per second
	float hintBorderX = 0.f; // pixels
	float speedIncrementPerUpgrade = 0.f; // pixels per second

	float GetStartScrollVelocity(const unsigned int upgradeCount) const;

public:
	float GetScrollVelocity(const unsigned int upgradeCount, const float elapsedSeconds) const;
	float GetHintBorderXCoord() const;

	// May throw a runtime_error if definitionfile is corrupt or missing
	void LoadFromFile(const std::string & definitionFile);
};

