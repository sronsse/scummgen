#include "Midi.hpp"
#include <fstream>
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/MIDFile.hpp"

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

	MIDFile midFile;
	if (!midFile.open(fileName))
		Log::getInstance().write(LOG_ERROR, "There was a problem reading file \"%s\" !\n", fileName.c_str());
	for (int i = 0; i < midFile.getNumberOfDataBytes(); i++)
		_dataBytes.push_back(midFile.getDataByte(i));

	Log::getInstance().unIndent();
}

Midi::~Midi()
{
}
