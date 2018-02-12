#include "stringutil.hpp"

namespace Util
{
	std::string GetStringInQuotes(const std::string & line)
	{
		std::string retval;

		const auto firstQuote = line.find('\"');
		if(firstQuote != std::string::npos)
		{
			const auto secondQuote = line.find('\"', firstQuote + 1);
			if(secondQuote != std::string::npos)
			{
				retval = line.substr(firstQuote + 1U, (secondQuote - 1U) - firstQuote);
			}
		}

		return retval;
	}
}