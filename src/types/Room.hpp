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
class Script;
class Declaration;
class Function;

class Room
{
private:
	static const string XML_FILE_NAME;
	static const uint8_t MIN_LOCAL_SCRIPT_ID;

	uint8_t _id;
	string _name;
	Palette *_palette;
	Image *_background;
	Map *_map;
	vector<Object *> _objects;
	vector<Script *> _scripts;
	vector<Costume *> _costumes;
	vector<Declaration *> _declarations;
	vector<Function *> _functions;
	Function *_entryFunction;
	Function *_exitFunction;

	void loadObjects(string dirPath, XMLNode *node);
	void loadScripts(string dirPath, XMLNode *node);
	void loadCostumes(string dirPath, XMLNode *node);
	void saveObjects(string dirPath, XMLNode *node);
	void saveScripts(string dirPath, XMLNode *node);
	void saveCostumes(string dirPath, XMLNode *node);
public:
	Room();
	void load(string dirPath);
	void save(string dirPath);
	void prepare(Palette *palette);
	void parse(vector<Declaration *> &declarations);
	void compile();
	uint8_t getID() { return _id; }
	void setID(uint8_t id) { _id = id; }
	string getName() { return _name; }
	Palette *getPalette() { return _palette; }
	void setPalette(Palette *palette) { _palette = palette; }
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
