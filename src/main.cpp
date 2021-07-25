#include "Controller.h"

int main()
{
	std::fstream excp;
	try
	{
		excp.open("log.txt", std::ios::app);
		if (!excp.is_open())
			throw std::exception("log file couldn't be open.\n");

		Controller game;
		game.startMenu();
	}
	catch (std::exception& e)
	{
		excp << e.what();
	}
	return EXIT_SUCCESS;
}
