#pragma once

namespace Player
{
	struct Score
	{
	private:
		unsigned int neutralizations;
		double bonusScore;

	public:
		double distance;

		double CalculateBonusScore(const double distance) const;
		double CalculateNeutralizationScore(const unsigned int count) const;
		double GetTotalScore() const;
		unsigned int GetCurrency() const;

		// Ups the neutralization count and adds the bonus score using the distance
		void AddNeutralization(const double distanceFromPlayer);

		void Reset();

		Score();
	};
}


