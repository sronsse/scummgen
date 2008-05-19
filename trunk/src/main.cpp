#include "Assembler.hpp"
#include <iostream>
#include <string>
#include "util/Log.hpp"
#include "types/Game.hpp"
using namespace std;

int main(int argc, char **argv)
{
	cout << "ScummGEN's assembler: version " << (int)Assembler::MAJOR_VERSION << '.' << (int)Assembler::MINOR_VERSION << '.' << Assembler::VERSION_TYPE << endl;
	Log::getInstance().setActive(true);

	string dirName = "data/loh/";
	cout << "Loading \"" << dirName << "\" game directory..." << endl;
	Game game(dirName);

	string outputDirName = "";
	cout << "Generating \"" << game.getLongName() << "\" resource files..." << endl;
	Assembler assembler(&game, outputDirName);

	return 0;
}

