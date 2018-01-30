#include "program.hpp"

#include <iostream>

const unsigned int windowWidth = 1280U;
const unsigned int windowHeight = 720U;

int main(int argc, char ** argv)
{
	Program * p;
	try
	{
		p = new Program(windowWidth, windowHeight, "fonts/commodore.ttf", "Smart Tales II");
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
