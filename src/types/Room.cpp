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

vector<Room *> Room::_instances;

Room *Room::getInstanceFromName(string roomName)
{
	for (int i = 0; i < _instances.size(); i++)
		if (_instances[i]->getName() == roomName)
			return _instances[i];
	return NULL;
}

Room::Room(string dirName)
{
	Log::getInstance().write("Room\n");
	Log::getInstance().indent();

	_instances.push_back(this);

	XMLFile xmlFile(dirName + "room.xml");
	XMLNode *node = xmlFile.getRootNode();
	
	_id = _instances.size();
	Log::getInstance().write("id: %u\n", _id);

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());
	
	uint32_t nZPlanes = node->getChild("nZPlanes")->getIntegerContent();
	Log::getInstance().write("nZPlanes: %u\n", nZPlanes);

	_background = new Image(dirName, "background.bmp", nZPlanes);
	_palette = new Palette(dirName);
	loadObjects(dirName + "objects/", nZPlanes);
	_map = new Map(dirName);
	_entryScript = new Script(dirName + "scripts/entry" + Script::EXTENSION);
	_exitScript = new Script(dirName + "scripts/exit" + Script::EXTENSION);
	loadScripts(dirName + "scripts/");
	loadCostumes(dirName + "costumes/");

	Log::getInstance().unIndent();
}

void Room::loadObjects(string dirName, uint32_t nZPlanes)
{
	XMLFile xmlFile(dirName + "objects.xml");
	XMLNode *node = xmlFile.getRootNode();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("object", i++)) != NULL)
		_objects.push_back(new Object(dirName + child->getStringContent() + "/", nZPlanes));
}

void Room::loadScripts(string dirName)
{
	XMLFile xmlFile(dirName + "scripts.xml");
	XMLNode *node = xmlFile.getRootNode();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("script", i++)) != NULL)
		_scripts.push_back(new Script(dirName + child->getStringContent() + Script::EXTENSION));
}

void Room::loadCostumes(string dirName)
{
	XMLFile xmlFile(dirName + "costumes.xml");
	XMLNode *node = xmlFile.getRootNode();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("costume", i++)) != NULL)
		_costumes.push_back(new Costume(dirName + child->getStringContent() + "/"));
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
	for (int i = 0; i < _scripts.size(); i++)
		delete _scripts[i];
	for (int i = 0; i < _costumes.size(); i++)
		delete _costumes[i];
}
