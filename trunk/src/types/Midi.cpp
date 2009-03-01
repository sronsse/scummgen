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

	static uint16_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %d\n", _id);

	XMLFile xmlFile;
	xmlFile.open(dirPath + "midi.xml");
	XMLNode *node = xmlFile.getRootNode();
	
	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_midiPath = dirPath + node->getChild("midiName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "midiPath: %s\n", _midiPath.c_str());

	Log::getInstance().unIndent();
}

Midi::~Midi()
{
}
