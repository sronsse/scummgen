#include "Voice.hpp"
#include <fstream>
#include "util/Log.hpp"
#include "util/WAVFile.hpp"
#include "util/XMLFile.hpp"

Voice::Voice(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Voice\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB - posA + 1);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	XMLFile xmlFile;
	xmlFile.open(dirName + "voice.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node != NULL)
	{
		int i = 0;
		XMLNode *child;
		while ((child = node->getChild("syncTime", i++)) != NULL)
		{
			_syncTimes.push_back(child->getIntegerContent());
			Log::getInstance().write(LOG_INFO, "syncTime: %u\n", _syncTimes[i - 1]);
		}
	}

	WAVFile wavFile;
	if (!wavFile.open(dirName + "voice.wav"))
		Log::getInstance().write(LOG_ERROR, "There was a problem reading file \"%s%s\" !\n", dirName.c_str(), "voice.wav");

	_sampleRate = wavFile.getSampleRate();
	Log::getInstance().write(LOG_INFO, "sampleRate: %u\n", _sampleRate);

	for (int i = 0; i < wavFile.getNumberOfDataBytes(); i++)
		_dataBytes.push_back(wavFile.getDataByte(i));

	Log::getInstance().unIndent();
}

Voice::~Voice()
{
}
