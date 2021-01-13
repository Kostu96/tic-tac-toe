#include "application.h"
#include <iostream>

int main()
{
	try
	{
		Application app;
		app.run();

		return EXIT_SUCCESS;
	}
	catch (std::exception & e)
	{
		std::cerr << "EXCEPTION: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
}
