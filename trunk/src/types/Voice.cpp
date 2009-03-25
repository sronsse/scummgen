#include "Voice.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Voice::Voice():
_name(""),
_wavePath("")
{
}

void Voice::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Voice\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "voice.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_wavePath = dirPath + rootNode->getChild("waveName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "wavePath: %s\n", _wavePath.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("syncTime", i++)) != NULL)
	{
		_syncTimes.push_back(child->getIntegerContent());
		Log::getInstance().write(LOG_INFO, "syncTime: %u\n", _syncTimes[i - 1]);
	}

	Log::getInstance().unIndent();
}

Voice::~Voice()
{
}
