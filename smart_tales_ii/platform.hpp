#pragma once
#include <string>
#include <vector>

namespace Platform
{
	// Throws a runtime error if file could not be found or read
	std::vector<std::string> LoadTextFile(const std::string & filelocation, const bool ignoreComments = false, const bool ignoreEmpty = false);
}
