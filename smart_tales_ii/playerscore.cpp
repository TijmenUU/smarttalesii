#include "playerscore.hpp"

#include <cmath>

namespace Player
{
	unsigned int Score::GetNeutralizationCurrency(const double distance)
	{
		const unsigned int score = 5U + static_cast<unsigned int>(std::round(distance / 100.f));
		currencyGained += score;
		++neutralizations;

		return score;
	}

	unsigned int Score::GetTotalCurrency() const
	{
		return currencyGained;
	}

	unsigned int Score::GetTotalNeutralizations() const
	{
		return neutralizations;
	}

	void Score::Reset()
	{
		neutralizations = 0U;
		currencyGained = 0U;
		distance = 0.0;
	}
}
