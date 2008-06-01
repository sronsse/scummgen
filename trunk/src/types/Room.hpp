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
class Sound;
class Costume;

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
	vector<Sound *> _sounds;
	vector<Costume *> _costumes;

	void loadObjects(string dirName);
	void loadScripts(string dirName);
	void loadCostumes(string dirName);
public:
	static Room *getInstanceFromName(string roomName);

	Room(string dirName);
	uint8_t getID() { return _id; }
	string getName() { return _name; }
	Image *getBackground() { return _background; }
	Palette *getPalette() { return _palette; }
	uint16_t getNumberOfObjects() { return _objects.size(); }
	Object *getObject(uint16_t index) { return _objects[index]; }
	Map *getMap() { return _map; }
	Script *getEntryScript() { return _entryScript; }
	Script *getExitScript() { return _exitScript; }
	uint16_t getNumberOfScripts() { return _scripts.size(); }
	Script *getScript(uint16_t index) { return _scripts[index]; }
	uint16_t getNumberOfSounds() { return _sounds.size(); }
	Sound *getSound(uint16_t index) { return _sounds[index]; }
	uint16_t getNumberOfCostumes() { return _costumes.size(); }
	Costume *getCostume(uint16_t index) { return _costumes[index]; }
	~Room();
};

#endif

