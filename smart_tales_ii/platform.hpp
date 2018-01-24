#pragma once
#include <string>
#include <vector>

namespace Platform
{
	// Throws a runtime error if file could not be found or read
	std::vector<std::string> LoadFile(const std::string & filelocation);
}
