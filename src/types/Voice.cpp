#include "Voice.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string Voice::XML_FILE_NAME = "voice.xml";

Voice::Voice():
_name(""),
_wavePath("")
{
}

void Voice::load(string dirPath)
{
	Log::write(LOG_INFO, "Voice\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	_wavePath = dirPath + rootNode->getChild("waveName")->getStringContent();
	Log::write(LOG_INFO, "wavePath: %s\n", _wavePath.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("syncTime", i)) != NULL)
	{
		_syncTimes.push_back(child->getIntegerContent());
		Log::write(LOG_INFO, "syncTime: %u\n", _syncTimes[i]);
		i++;
	}

	Log::unIndent();
}

void Voice::save(string dirPath)
{
	Log::write(LOG_INFO, "Voice\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("voice");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	rootNode->addChild(new XMLNode("description", _description));
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	string waveName = _wavePath.substr(_wavePath.find_last_of('/') + 1);
	rootNode->addChild(new XMLNode("waveName", waveName));
	string newWavePath = dirPath + waveName;
	if (_wavePath != newWavePath)
	{
		if (!IO::copyFile(_wavePath, newWavePath))
			Log::write(LOG_ERROR, "Could not copy file \"%s\" to \"%s\" !\n", _wavePath.c_str(), newWavePath.c_str());
		_wavePath = newWavePath;
	}
	Log::write(LOG_INFO, "wavePath: %s\n", _wavePath.c_str());

	for (int i = 0; i < _syncTimes.size(); i++)
	{
		rootNode->addChild(new XMLNode("syncTime", _syncTimes[i]));
		Log::write(LOG_INFO, "syncTime: %u\n", _syncTimes[i]);
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save voice to the specified directory !\n");

	Log::unIndent();
}

Voice::~Voice()
{
}
