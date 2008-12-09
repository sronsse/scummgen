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
class Sound;
class Costume;
class Declaration;
class Function;

class Room
{
private:
	static const uint8_t MIN_LOCAL_ID;

	string _name;
	uint8_t _id;
	Image *_background;
	Palette *_palette;
	vector<Object *> _objects;
	Map *_map;
	vector<string> _scripts;
	vector<Sound *> _sounds;
	vector<Costume *> _costumes;
	Function *_entryFunction;
	Function *_exitFunction;
	vector<Declaration *> _declarations;
	vector<Function *> _functions;

	void loadObjects(string dirName);
	void loadScripts(string dirName);
	void loadCostumes(string dirName);
public:
	Room(string dirName);
	void parse(vector<Declaration *> &declarations);
	void compile();
	string getName() { return _name; }
	uint8_t getID() { return _id; }
	Image *getBackground() { return _background; }
	Palette *getPalette() { return _palette; }
	uint16_t getNumberOfObjects() { return _objects.size(); }
	Object *getObject(uint16_t index) { return _objects[index]; }
	Map *getMap() { return _map; }
	uint16_t getNumberOfSounds() { return _sounds.size(); }
	Sound *getSound(uint16_t index) { return _sounds[index]; }
	uint16_t getNumberOfCostumes() { return _costumes.size(); }
	Costume *getCostume(uint16_t index) { return _costumes[index]; }
	Function *getEntryFunction() { return _entryFunction; }
	Function *getExitFunction() { return _exitFunction; }
	uint8_t getNumberOfFunctions() { return _functions.size(); }
	Function *getFunction(uint8_t index) { return _functions[index]; }
	~Room();
};

#endif

