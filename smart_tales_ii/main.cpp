#include "program.hpp"
#include "soundmanager.hpp"

#include <algorithm>
#include <iostream>
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
	const static std::array<std::string, 2> values = {"debug", "nosound"};
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

	Program * p;
	try
	{
		p = new Program(windowWidth, windowHeight, "Smart Tales II", debug);
		p->Load();
	}
	catch(const std::runtime_error & e)
	{
		std::cout << "Error during game initialization: " << e.what() << std::endl;
		std::cout << "Press any key to exit...";
		std::cin.get();
		return 1;
	}
	 
	p->Run();
	delete p;

	return 0;
}
