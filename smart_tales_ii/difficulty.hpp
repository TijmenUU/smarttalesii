#pragma once
#include <string>

class Difficulty
{
private:
	float startVelocity = 0.f;	// pixels per second
	float incrementVelocity = 0.f; // pixels per second
	float maxVelocity = 0.f; // pixels per second
	float hintBorderX = 0.f; // pixels

public:
	float GetStartScrollVelocity() const;
	float GetScrollIncrementVelocity() const;
	float GetMaxScrollVelocity() const;
	float GetHintBorderXCoord() const;

	// May throw a runtime_error if definitionfile is corrupt or missing
	void LoadFromFile(const std::string & definitionFile);
};

