#include <iostream>
#include <string>
#include "util/Log.hpp"
#include "ScummGEN.hpp"
using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <game directory>\n";
		return 0;
	}

	cout << "ScummGEN version " << (int)ScummGEN::MAJOR_VERSION << '.' << (int)ScummGEN::MINOR_VERSION << '.' << ScummGEN::VERSION_TYPE << endl;

	Log::getInstance().setActive(true);

	// First, we load our game data structure using the game directory as an input,
	// taking care of any exception which could occur
	try
	{
		ScummGEN::getInstance().load(argv[1]);
	}
	catch (int e)
	{
		return e;
	}

	// Then, we generate the final resources
	ScummGEN::getInstance().generate("");

	cout << "Game generated successfully !\n";
	return 0;
}

