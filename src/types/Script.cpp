#include "Script.hpp"
#include <fstream>
#include "util/Log.hpp"

Script::Script(string fileName)
{
	Log::getInstance().write("Script\n");
	Log::getInstance().indent();

	Log::getInstance().write("fileName: %s\n", fileName.c_str());

	_id = 1; // tmp
	Log::getInstance().write("id: %u\n", _id);

	Log::getInstance().unIndent();
}

Script::~Script()
{
}

