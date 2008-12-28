#include "WAVFile.hpp"
#include <fstream>
#include "IO.hpp"
#include "Log.hpp"

WAVFile::WAVFile()
{
}

bool WAVFile::open(string fileName)
{
	// We open the file, which should be an 8bit PCM Wave file
	fstream file(fileName.c_str(), ios::in | ios::binary);
	if (!file.is_open())
	{
		Log::getInstance().write(LOG_WARNING, "Couldn't open file !\n");
		return false;
	}

	IO::readU32LE(file); // "RIFF" block
	IO::readU32LE(file); // chunkSize
	IO::readU32LE(file); // format
	IO::readU32LE(file); // "fmt " block
	IO::readU32LE(file); // chunkSize

	uint16_t audioFormat = IO::readU16LE(file);
	// Only PCM is supported
	if (audioFormat != 1)
	{
		file.close();
		Log::getInstance().write(LOG_WARNING, "Audio format not supported !\n");
		return false;
	}

	IO::readU16LE(file); // nChannels
	_sampleRate = IO::readU32LE(file);
	IO::readU32LE(file); // byteRate
	IO::readU16LE(file); // blockAlign

	uint16_t bitsPerSample = IO::readU16LE(file);
	// Only 8bit is supported
	if (bitsPerSample != 8)
	{
		file.close();
		Log::getInstance().write(LOG_WARNING, "Bits per sample not supported !\n");
		return false;
	}

	IO::readU32LE(file); // "data" block

	uint32_t nDataBytes = IO::readU32LE(file);
	for (int i = 0; i < nDataBytes; i++)
		_dataBytes.push_back(IO::readU8(file));

	file.close();

	return true;
}

WAVFile::~WAVFile()
{
}
