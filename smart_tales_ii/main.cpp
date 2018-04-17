#include "program.hpp"

#include <iostream>
#include <string>

const unsigned int windowWidth = 1280U;
const unsigned int windowHeight = 720U;

int main(int argc, char ** argv)
{
	bool debug = false;
	if(argc >= 2 && std::string(argv[1]).compare("debug") == 0)
	{
		debug = true;
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
