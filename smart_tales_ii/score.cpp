#include "score.hpp"

#include <cmath>

void Score::AddNeutralization(const float distanceFromPlayer)
{
	++neutralizations;

	bonusScore += (distanceFromPlayer / 1280.f) * 200.f;
}

double Score::GetTotalScore()
{
	return std::abs((distance / 100.0) + (static_cast<double>(neutralizations) * 50.0) + bonusScore);
}

unsigned int Score::GetCurrency()
{
	return static_cast<unsigned int>(std::round(GetTotalScore() / 100.0));
}

void Score::Reset()
{
	neutralizations = 0U;
	bonusScore = 0.0;
	distance = 0.0;
}

Score::Score()
	: neutralizations(0U),
	bonusScore(0.0),
	distance(0.0)
{
}
