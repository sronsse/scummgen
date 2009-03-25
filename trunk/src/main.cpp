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

	Log::getInstance().setActive(true);

	Game game;

	// First, we load our game data structure using the game directory as an input,
	// taking care of any exception which could occur
	string dirPath = argv[1];
	try
	{
		game.load(dirPath);
		game.build("");
	}
	catch (int e)
	{
		return e;
	}

	cout << "Game generated successfully !\n";
	return 0;
}

