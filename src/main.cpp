#include "Assembler.hpp"
#include <iostream>
#include <string>
#include "util/Log.hpp"
#include "types/Game.hpp"
using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <game directory>\n";
		return 0;
	}

	cout << "ScummGEN's assembler: version " << (int)Assembler::MAJOR_VERSION << '.' << (int)Assembler::MINOR_VERSION << '.' << Assembler::VERSION_TYPE << endl;
	Log::getInstance().setActive(true);

	string dirName = argv[1];
	cout << "Loading \"" << dirName << "\" game directory..." << endl;
	Game game(dirName);

	string outputDirName = "";
	cout << "Generating \"" << game.getLongName() << "\" resource files..." << endl;
	Assembler assembler(&game, outputDirName);

	return 0;
}

