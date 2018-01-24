#include "platform.hpp"

#include <fstream>
#include <stdexcept>

namespace Platform
{
	std::vector<std::string> LoadFile(const std::string & filelocation)
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
			result.push_back(line);
		}

		return result;
	}
}
