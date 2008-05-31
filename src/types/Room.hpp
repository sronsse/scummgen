#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Image;
class Palette;
class Object;
class Map;
class Script;
class Costume;
class Charset;

class Room
{
private:
	static vector<Room *> _instances;

	uint8_t _id;
	string _name;
	Image *_background;
	Palette *_palette;
	vector<Object *> _objects;
	Map *_map;
	Script *_entryScript;
	Script *_exitScript;
	vector<Script *> _scripts;
	vector<Costume *> _costumes;

	void loadObjects(string dirName, uint32_t nZPlanes);
	void loadScripts(string dirName);
	void loadCostumes(string dirName);
public:
	static Room *getInstanceFromName(string roomName);

	Room(string dirName);
	uint8_t getID() { return _id; }
	string getName() { return _name; }
	Image *getBackground() { return _background; }
	Palette *getPalette() { return _palette; }
	uint32_t getNumberOfObjects() { return _objects.size(); }
	Object *getObject(uint32_t index) { return _objects[index]; }
	Map *getMap() { return _map; }
	Script *getEntryScript() { return _entryScript; }
	Script *getExitScript() { return _exitScript; }
	uint32_t getNumberOfScripts() { return _scripts.size(); }
	Script *getScript(uint32_t index) { return _scripts[index]; }
	uint32_t getNumberOfCostumes() { return _costumes.size(); }
	Costume *getCostume(uint32_t index) { return _costumes[index]; }
	~Room();
};

#endif

