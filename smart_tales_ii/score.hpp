#pragma once

struct Score
{
protected:
	unsigned int neutralizations;
	double bonusScore;

public:
	double distance;

	void AddNeutralization(const float distanceFromPlayer);

	double GetTotalScore();
	unsigned int GetCurrency();

	void Reset();

	Score();
};

