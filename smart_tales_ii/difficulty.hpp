#pragma once
#include <string>

class Difficulty
{
private:
	float startVelocity;	// pixels per second
	float incrementVelocity; // pixels per second
	float maxVelocity; // pixels per second
	float hintBorderX; // pixels

public:
	float GetStartScrollVelocity() const;
	float GetScrollIncrementVelocity() const;
	float GetMaxScrollVelocity() const;
	float GetHintBorderXCoord() const;

	// May throw a runtime_error if definitionfile is corrupt or missing
	void LoadFromFile(const std::string & definitionFile);

	Difficulty();
};

