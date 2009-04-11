#include <iostream>
#include <string>
#include <config.h>
#include "util/Log.hpp"
#include "types/Game.hpp"
using namespace std;

int main(int argc, char **argv)
{
	cout << PACKAGE_STRING << endl;

	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <game directory>\n";
		return 0;
	}

	Log::reset();

	// Load and build the game directory passed as an argument
	try
	{
		Game game;
		game.load(argv[1]);
		game.build("");
	}
	catch (int e)
	{
		return e;
		Log::close();
	}

	Log::close();
	cout << "Game generated successfully !\n";

	return 0;
}
