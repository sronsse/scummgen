#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;
class Room;
class Object;
class Costume;
class Charset;
class Voice;
class Declaration;
class Function;

class Array
{
private:
	uint16_t _varNumber;
	uint16_t _dimA;
	uint16_t _dimB;
	uint16_t _type;
public:
	Array(XMLNode *node);
	uint16_t getVarNumber() { return _varNumber; }
	uint16_t getDimA() { return _dimA; }
	uint16_t getDimB() { return _dimB; }
	uint16_t getType() { return _type; }
	~Array();
};

class Game
{
private:
	string _longName;
	string _shortName;
	uint8_t _key;
	vector<Array *> _arrays;
	vector<Room *> _rooms;
	vector<Object *> _objects;
	vector<string> _scripts;
	vector<Costume *> _costumes;
	vector<Charset *> _charsets;
	vector<Voice *> _voices;
	vector<Declaration *> _declarations;
	vector<Function *> _functions;

	void loadObjects(string dirName);
	void loadCostumes(string dirName);
	void loadRooms(string dirName);
	void loadScripts(string dirName);
	void loadCharsets(string dirName);
	void loadVoices(string dirName);
public:
	static const uint8_t N_DEFAULT_ACTORS;
	static const uint16_t MAX_WORD_VARIABLES;
	static const uint8_t MAX_LOCAL_VARIABLES;

	Game(string dirName);
	void parse();
	void compile();
	string getLongName() { return _longName; }
	string getShortName() { return _shortName; }
	uint8_t getKey() { return _key; }
	uint16_t getNumberOfArrays() { return _arrays.size(); }
	Array *getArray(uint16_t index) { return _arrays[index]; }
	uint8_t getNumberOfRooms() { return _rooms.size(); }
	Room *getRoom(uint8_t index) { return _rooms[index]; }
	uint16_t getNumberOfObjects() { return _objects.size(); }
	Object *getObject(uint16_t index) { return _objects[index]; }
	uint16_t getNumberOfCostumes() { return _costumes.size(); }
	Costume *getCostume(uint16_t index) { return _costumes[index]; }
	uint8_t getNumberOfCharsets() { return _charsets.size(); }
	Charset *getCharset(uint8_t index) { return _charsets[index]; }
	uint16_t getNumberOfVoices() { return _voices.size(); }
	Voice *getVoice(uint16_t index) { return _voices[index]; }
	void addFunction(Function *function) { _functions.push_back(function); }
	uint16_t getNumberOfFunctions() { return _functions.size(); }
	Function *getFunction(uint16_t index) { return _functions[index]; }
	~Game();
};

#endif

