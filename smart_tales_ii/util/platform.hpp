/*
	platform.hpp

	This file was originally created for compatability with potential android
	builds later on. What is left is pure legacy functionality, as the loading
	of assets are all done through SFML with hardcoded values.

	This function is still used by
	- ../game/difficulty.cpp
	- ../game/animation/animationsheet.cpp
*/

#pragma once
#include <string>
#include <vector>

namespace Util
{
	// Throws a runtime error if file could not be found or read
	std::vector<std::string> LoadTextFile(const std::string & filelocation, const bool ignoreComments = false, const bool ignoreEmpty = false);
}
