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

	// Asumes directories only contain alphanumeric characters
	std::string GetFileName(const std::string & path)
	{
		if(path.size() == 0)
		{
			return "";
		}

		size_t end = path.size();
		size_t start = 0;
		size_t i = path.size() - 1;
		do
		{
			if(path[i] == '.')
			{
				end = i;
			}
			else if(path[i] == '/')
			{
				start = i + 1;
				break;
			}
			--i;
		} while(i != 0);

		return path.substr(start, end - start);
	}
}