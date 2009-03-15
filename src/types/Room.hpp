#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;
class Image;
class Palette;
class Object;
class Map;
class Costume;
class Declaration;
class Function;

class Room
{
private:
	static const uint8_t MIN_LOCAL_ID;

	uint8_t _id;
	string _name;
	Palette *_palette;
	Image *_background;
	Map *_map;
	vector<Object *> _objects;
	vector<string> _scripts;
	vector<Costume *> _costumes;
	Function *_entryFunction;
	Function *_exitFunction;
	vector<Declaration *> _declarations;
	vector<Function *> _functions;

	void loadObjects(string dirPath, XMLNode *node);
	void loadScripts(string dirPath, XMLNode *node);
	void loadCostumes(string dirPath, XMLNode *node);
	void addDeclarations();
public:
	Room();
	void load(string dirPath);
	void parse(vector<Declaration *> &declarations);
	void compile();
	string getName() { return _name; }
	uint8_t getID() { return _id; }
	Palette *getPalette() { return _palette; }
	Image *getBackground() { return _background; }	
	Map *getMap() { return _map; }
	uint16_t getNumberOfObjects() { return _objects.size(); }
	Object *getObject(uint16_t index) { return _objects[index]; }
	uint16_t getNumberOfCostumes() { return _costumes.size(); }
	Costume *getCostume(uint16_t index) { return _costumes[index]; }
	Function *getEntryFunction() { return _entryFunction; }
	Function *getExitFunction() { return _exitFunction; }
	uint8_t getNumberOfFunctions() { return _functions.size(); }
	Function *getFunction(uint8_t index) { return _functions[index]; }
	~Room();
};

#endif
