#include "Midi.hpp"
#include <fstream>
#include "util/IO.hpp"
#include "util/Log.hpp"

Midi::Midi(string fileName)
{
	Log::getInstance().write(LOG_INFO, "Midi\n");
	Log::getInstance().indent();

	int posA = fileName.find_last_of('/') + 1;
	int posB = fileName.find_last_of('.') - 1;
	
	_name = fileName.substr(posA, posB - posA + 1);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	static uint16_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %d\n", _id);

	fstream file(fileName.c_str(), ios::in | ios::binary);
	file.seekg(0, ios::end);
	uint32_t fileSize = file.tellg();
	file.seekp(0, ios::beg);
	for (int i = 0; i < fileSize; i++)
		_dataBytes.push_back(IO::readU8(file));

	Log::getInstance().unIndent();
}

Midi::~Midi()
{
}
