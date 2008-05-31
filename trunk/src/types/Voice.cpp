#include "Voice.hpp"
#include <fstream>
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

vector<Voice *> Voice::_instances;

Voice *Voice::getInstanceFromName(string voiceName)
{
	for (int i = 0; i < _instances.size(); i++)
		if (_instances[i]->getName() == voiceName)
			return _instances[i];
	return NULL;
}

Voice::Voice(string dirName)
{
	Log::getInstance().write("Voice\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	XMLFile xmlFile(dirName + "voice.xml");
	XMLNode *node = xmlFile.getRootNode();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("syncTime", i++)) != NULL)
	{
		_syncTimes.push_back(child->getIntegerContent());
		Log::getInstance().write("syncTime: %u\n", _syncTimes[_syncTimes.size() - 1]);
	}

	loadWAV(dirName + "voice.wav");

	Log::getInstance().unIndent();
}

void Voice::loadWAV(string fileName)
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
	uint8_t dataByte;
	for (int i = 0; i < nDataBytes; i++)
	{
		file.read((char *)&dataByte, 1);
		_dataBytes.push_back(dataByte);
	}

	file.close();
}

Voice::~Voice()
{
}
