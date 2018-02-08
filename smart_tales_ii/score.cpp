#include "score.hpp"

#include <cmath>

double Score::CalculateBonusScore(const double distance) const
{
	return (distance / 1280.0) * 200.0;
}

double Score::CalculateNeutralizationScore(const unsigned int count) const
{
	return static_cast<double>(count) * 50.0;
}

double Score::GetTotalScore() const
{
	return std::abs((distance / 100.0) + CalculateNeutralizationScore(neutralizations) + bonusScore);
}

unsigned int Score::GetCurrency() const
{
	return static_cast<unsigned int>(std::round(GetTotalScore() / 100.0));
}

void Score::AddNeutralization(const double distanceFromPlayer)
{
	++neutralizations;

	bonusScore += CalculateBonusScore(distanceFromPlayer);
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
