#include "platform.hpp"

#include <fstream>
#include <stdexcept>

namespace Platform
{
	const char cCommentChar = '#';

	std::vector<std::string> LoadTextFile(const std::string & filelocation, const bool ignoreComments, const bool ignoreEmpty)
	{
		std::vector<std::string> result;
		
		std::ifstream inputfile;
		inputfile.open(filelocation, std::ios::in);
		if(!inputfile.is_open())
		{
			throw std::runtime_error("Error reading " + filelocation);
		}

		while(inputfile.good())
		{
			std::string line;
			std::getline(inputfile, line);
			
			if((ignoreEmpty && line.size() == 0U) || (ignoreComments && line[0] == cCommentChar))
				continue;

			result.push_back(line);
		}

		return result;
	}
}
