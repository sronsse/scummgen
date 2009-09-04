#include "Midi.hpp"
#include <fstream>
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string Midi::XML_FILE_NAME = "midi.xml";

Midi::Midi():
_id(0),
_name(""),
_midiPath("")
{
}

void Midi::load(string dirPath)
{
	Log::write(LOG_INFO, "Midi\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();
	
	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_midiPath = dirPath + rootNode->getChild("midiName")->getStringContent();
	Log::write(LOG_INFO, "midiPath: %s\n", _midiPath.c_str());

	Log::unIndent();
}

void Midi::save(string dirPath)
{
	Log::write(LOG_INFO, "Midi\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("midi");
	xmlFile.setRootNode(rootNode);
	
	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	string midiName = _midiPath.substr(_midiPath.find_last_of('/') + 1);
	rootNode->addChild(new XMLNode("midiName", midiName));
	string newMidiPath = dirPath + midiName;
	if (_midiPath != newMidiPath)
	{
		if (!IO::copyFile(_midiPath, newMidiPath))
			Log::write(LOG_ERROR, "Could not copy file \"%s\" to \"%s\" !\n", _midiPath.c_str(), newMidiPath.c_str());
		_midiPath = newMidiPath;
	}
	Log::write(LOG_INFO, "midiPath: %s\n", _midiPath.c_str());

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save midi to the specified directory !\n");

	Log::unIndent();
}

Midi::~Midi()
{
}
