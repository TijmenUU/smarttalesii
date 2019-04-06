/*
	stringutil.hpp

	Small collection of string functions used by the callers
	that do file io. The difficulty file parsing and the ResourceCache 
	class	are the main users of these.
*/

#pragma once
#include <string>

namespace Util
{
	std::string GetStringInQuotes(const std::string & line);

	std::string GetFileName(const std::string & path);
}
