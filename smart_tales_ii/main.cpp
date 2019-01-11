/*
	main.cpp

	Any launch parameters given to the executable are parsed here, 
	the program instantiated and loaded. If any errors occur during 
	the loading of assets, the game will output the error to console.
*/

#include "program.hpp"
#include "soundmanager.hpp"

#include <algorithm>
#include <cstdio>
#include <memory>
#include <string>

const unsigned int windowWidth = 1280U;
const unsigned int windowHeight = 720U;

enum class LaunchParameter
{
	Unknown = -1,
	Debug,
	NoSound
};

LaunchParameter GetLaunchParameterToken(const std::string & s)
{
	const std::array<std::string, 2> values = {"debug", "nosound"};
	for(size_t i = 0; i < values.size(); ++i)
	{
		if(values[i].compare(s) == 0)
		{
			return static_cast<LaunchParameter>(i);
		}
	}

	return LaunchParameter::Unknown;
}

int main(int argc, char ** argv)
{
	bool debug = false;

	// Parse the launch parameters
	for(size_t i = 1; i < argc; ++i)
	{
		const auto result = GetLaunchParameterToken(argv[i]);
		switch(result)
		{
			case LaunchParameter::Debug:
			debug = true;
			break;

			case LaunchParameter::NoSound:
			{
				auto & instance = SoundManager::GetInstance();
				instance.SetMusicMute(true);
				instance.SetSFXMute(true);
			}
			break;

			default:
			case LaunchParameter::Unknown:
			break;
		}
	}

	std::unique_ptr<Program> programPtr(new Program(windowWidth, 
		windowHeight, 
		"Smart Tales II", 
		debug));

	try
	{
		programPtr->Load();
	}
	catch(const std::runtime_error & e)
	{
		std::printf("Error during game initialization: %s\n", e.what());
		std::printf("Press any key to exit...");
		std::getchar();
		return 1;
	}
	 
	programPtr->Run();

	return 0;
}
