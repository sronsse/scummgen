#include "Sound.hpp"
#include <fstream>
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Sound::Sound(string dirName)
{
	Log::getInstance().write("Sound\n");
	Log::getInstance().indent();

	XMLFile xmlFile(dirName + "sound.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_id = rootNode->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %u\n", _id);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("syncTime", i++)) != NULL)
		_syncTimes.push_back(child->getIntegerContent());
	Log::getInstance().write("nSyncTimes: %u\n", _syncTimes.size());

	loadWAV(dirName + "sound.wav");
	Log::getInstance().write("sampleRate: %u\n", _sampleRate);
	Log::getInstance().write("nDataBytes: %u\n", _dataBytes.size());

	Log::getInstance().unIndent();
}

void Sound::loadWAV(string fileName)
{
	// We open the file, which should be an 8bit PCM Wave file
	ifstream file(fileName.c_str(), ios::in | ios::binary);
	if (!file.is_open())
		return;

	// We start by reading the "RIFF" block
	char chunkID[5];
	file.read((char *)&chunkID, 4);
	chunkID[4] = 0;

	uint32_t chunkSize;
	file.read((char *)&chunkSize, 4);

	uint8_t format[5];
	file.read((char *)&format, 4);
	format[4] = 0;

	// Then the "fmt " block follows
	file.read((char *)&chunkID, 4);

	file.read((char *)&chunkSize, 4);

	uint16_t audioFormat;
	file.read((char *)&audioFormat, 2);
	// Only PCM is supported
	if (audioFormat != 1)
	{
		file.close();
		return;
	}

	uint16_t nChannels;
	file.read((char *)&nChannels, 2);

	file.read((char *)&_sampleRate, 4);

	uint32_t byteRate;
	file.read((char *)&byteRate, 4);

	uint16_t blockAlign;
	file.read((char *)&blockAlign, 2);

	uint16_t bitsPerSample;
	file.read((char *)&bitsPerSample, 2);
	// Only 8bit is supported
	if (bitsPerSample != 8)
	{
		file.close();
		return;
	}

	// We end by reading the "data" block
	file.read((char *)&chunkID, 4);
	
	uint32_t nDataBytes;
	file.read((char *)&nDataBytes, 4);
	uint8_t byte;
	for (int i = 0; i < nDataBytes; i++)
	{
		file.read((char *)&byte, 1);
		_dataBytes.push_back(byte);
	}

	file.close();
}

Sound::~Sound()
{
}

