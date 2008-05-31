#include "Script.hpp"
#include <fstream>
#include "util/Log.hpp"

const string Script::EXTENSION = ".sgc";

Script::Script(string fileName)
{
	Log::getInstance().write("Script\n");
	Log::getInstance().indent();

	int posB = fileName.find_last_of('.') - 1;
	int posA = fileName.find_last_of('/') + 1;
	_name = fileName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	_id = 1; // tmp
	Log::getInstance().write("id: %u\n", _id);

	Log::getInstance().unIndent();
}

Script::~Script()
{
}

