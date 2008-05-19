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
	uint8_t _id;
	string _name;
	Image *_background;
	Palette *_palette;
	vector<Object *> _objects;
	Map *_map;
	Script *_entryScript;
	Script *_exitScript;
	vector<Script *> _localScripts;
	vector<Script *> _globalScripts;
	vector<Costume *> _costumes;
	vector<Charset *> _charsets;
public:
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
	uint32_t getNumberOfLocalScripts() { return _localScripts.size(); }
	Script *getLocalScript(uint32_t index) { return _localScripts[index]; }
	uint32_t getNumberOfGlobalScripts() { return _globalScripts.size(); }
	Script *getGlobalScript(uint32_t index) { return _globalScripts[index]; }
	uint32_t getNumberOfCostumes() { return _costumes.size(); }
	Costume *getCostume(uint32_t index) { return _costumes[index]; }
	uint32_t getNumberOfCharsets() { return _charsets.size(); }
	Charset *getCharset(uint32_t index) { return _charsets[index]; }
	~Room();
};

#endif

