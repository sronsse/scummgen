#include "Room.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Image.hpp"
#include "Palette.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Script.hpp"
#include "Costume.hpp"
#include "Charset.hpp"

Room::Room(string dirName)
{
	Log::getInstance().write("Room\n");
	Log::getInstance().indent();

	XMLFile xmlFile(dirName + "room.xml");
	XMLNode *node = xmlFile.getRootNode();
	
	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %u\n", _id);

	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write("name: %s\n", _name.c_str());

	uint32_t nObjects = node->getChild("nObjects")->getIntegerContent();
	Log::getInstance().write("nObjects: %u\n", nObjects);
	
	uint32_t nZPlanes = node->getChild("nZPlanes")->getIntegerContent();
	Log::getInstance().write("nZPlanes: %u\n", nZPlanes);

	uint32_t nLocalScripts = node->getChild("nLocalScripts")->getIntegerContent();
	Log::getInstance().write("nLocalScripts: %u\n", nLocalScripts);

	uint32_t nGlobalScripts = node->getChild("nGlobalScripts")->getIntegerContent();
	Log::getInstance().write("nGlobalScripts: %u\n", nGlobalScripts);

	uint32_t nCostumes = node->getChild("nCostumes")->getIntegerContent();
	Log::getInstance().write("nCostumes: %u\n", nCostumes);

	uint32_t nCharsets = node->getChild("nCharsets")->getIntegerContent();
	Log::getInstance().write("nCharsets: %u\n", nCharsets);

	_background = new Image(dirName, "background.bmp", false, nZPlanes);

	_palette = new Palette(dirName);

	for (int i = 0; i < nObjects; i++)
		_objects.push_back(new Object(dirName + "objects/object_" + IO::getStringFromIndex(i, 3) + "/", nZPlanes));

	_map = new Map(dirName);

	_entryScript = new Script(dirName + "scripts/entry.txt");

	_exitScript = new Script(dirName + "scripts/exit.txt");

	for (int i = 0; i < nLocalScripts; i++)
		_localScripts.push_back(new Script(dirName + "scripts/local/local_" + IO::getStringFromIndex(i, 3) + ".txt"));

	for (int i = 0; i < nGlobalScripts; i++)
		_globalScripts.push_back(new Script(dirName + "scripts/global/global_" + IO::getStringFromIndex(i, 3) + ".txt"));

	for (int i = 0; i < nCostumes; i++)
		_costumes.push_back(new Costume(dirName + "costumes/costume_" + IO::getStringFromIndex(i, 3) + "/"));

	for (int i = 0; i < nCharsets; i++)
		_charsets.push_back(new Charset(dirName + "charsets/charset_" + IO::getStringFromIndex(i, 3) + "/"));

	Log::getInstance().unIndent();
}

Room::~Room()
{
	delete _background;
	delete _palette;
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];
	delete _map;
	delete _entryScript;
	delete _exitScript;
	for (int i = 0; i < _localScripts.size(); i++)
		delete _localScripts[i];
	for (int i = 0; i < _globalScripts.size(); i++)
		delete _globalScripts[i];
	for (int i = 0; i < _costumes.size(); i++)
		delete _costumes[i];
	for (int i = 0; i < _charsets.size(); i++)
		delete _charsets[i];
}

