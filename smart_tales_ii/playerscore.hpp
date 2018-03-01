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

		static double CalculateBonusScore(const double distance);
		static double CalculateNeutralizationScore(const unsigned int count);

		double GetTotalScore() const;
		unsigned int GetCurrency() const;

		// Ups the neutralization count and adds the bonus score using the distance
		void AddNeutralization();
		void AddBonusScore(const double score);

		void Reset();

		Score();
	};
}


