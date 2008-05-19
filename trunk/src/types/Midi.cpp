#include "Midi.hpp"
#include <fstream>
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Midi::Midi(string dirName)
{
	Log::getInstance().write("Midi\n");
	Log::getInstance().indent();

	Log::getInstance().unIndent();
}

Midi::~Midi()
{
}

