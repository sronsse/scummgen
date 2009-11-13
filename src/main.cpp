#include <iostream>
#include <string>
#include <config.h>
#include "util/Log.hpp"
#include "types/Game.hpp"
using namespace std;

string getProgramDirPath(string programPath)
{
	size_t pos = programPath.find_last_of("/\\");
	if (pos != string::npos)
		return programPath.substr(0, pos + 1);
	return "";
}

int main(int argc, char **argv)
{
	cout << PACKAGE_STRING << endl;

	// Check arguments
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
		game.build(getProgramDirPath(argv[0]), "");
	}
	catch (int e)
	{
		Log::close();
		return e;
	}

	Log::close();
	cout << "Game generated successfully !\n";

	return 0;
}
