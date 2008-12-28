#include "MIDFile.hpp"
#include <fstream>
#include "IO.hpp"
#include "Log.hpp"

MIDFile::MIDFile()
{
}

bool MIDFile::open(string fileName)
{
	// We open the file
	fstream file(fileName.c_str(), ios::in | ios::binary);
	if (!file.is_open())
	{
		Log::getInstance().write(LOG_WARNING, "Couldn't open file !\n");
		return false;
	}

	// This only works with MIDI format 2
	// TODO: convert format 1 to format 2
	file.seekg(0, ios::end);
	uint32_t fileSize = file.tellg();
	file.seekp(0, ios::beg);
	for (int i = 0; i < fileSize; i++)
		_dataBytes.push_back(IO::readU8(file));

	return true;
}

MIDFile::~MIDFile()
{
}
