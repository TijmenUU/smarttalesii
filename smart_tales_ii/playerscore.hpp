#pragma once

namespace Player
{
	class Score
	{
	private:
		unsigned int neutralizations = 0U;
		unsigned int currencyGained = 0U;

	public:
		double distance;

		// Returns the currency reward for neutralizing an obstacle
		// but accumulates these rewards internally as well
		unsigned int GetNeutralizationCurrency(const double distance);

		unsigned int GetTotalCurrency() const;
		unsigned int GetTotalNeutralizations() const;

		void Reset();
	};
}


