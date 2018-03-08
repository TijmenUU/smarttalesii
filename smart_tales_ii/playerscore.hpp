#pragma once

namespace Player
{
	struct Score
	{
	private:
		unsigned int neutralizations;
		unsigned int currencyGained;

	public:
		double distance;

		// Returns the currency reward for neutralizing an obstacle
		// but accumulates these rewards internally as well
		unsigned int GetNeutralizationCurrency(const double distance);

		unsigned int GetTotalCurrency() const;
		unsigned int GetTotalNeutralizations() const;

		void Reset();

		Score();
	};
}


