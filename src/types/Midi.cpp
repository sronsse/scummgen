#include "Midi.hpp"
#include <fstream>
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Midi::Midi():
_name(""),
_midiPath("")
{
}

void Midi::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Midi\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "midi.xml");
	XMLNode *rootNode = xmlFile.getRootNode();
	
	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_midiPath = dirPath + rootNode->getChild("midiName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "midiPath: %s\n", _midiPath.c_str());

	Log::getInstance().unIndent();
}

Midi::~Midi()
{
}
