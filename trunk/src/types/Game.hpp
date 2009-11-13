#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class XMLNode;
class Room;
class Object;
class Midi;
class Costume;
class Charset;
class Voice;
class Script;
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
	Array();
	void load(XMLNode *node);
	void save(XMLNode *node);
	uint16_t getVarNumber() { return _varNumber; }
	uint16_t getDimA() { return _dimA; }
	uint16_t getDimB() { return _dimB; }
	uint16_t getType() { return _type; }
	~Array();
};

class Game
{
private:
	static const string XML_FILE_NAME;
	static const char *INDEX_FILE_EXTENSION;
	static const char *RESOURCE_FILE_EXTENSION;
	static const char *VOICE_FILE_NAME;
	static const string LIB_SCUMM_DIR_PATH;
	static const string ACTOR_SCRIPT_NAME;
	static const string INTERFACE_SCRIPT_NAME;
	static const string OBJECT_SCRIPT_NAME;
	static const string ROOM_SCRIPT_NAME;
	static const string SCRIPT_SCRIPT_NAME;
	static const string SOUND_SCRIPT_NAME;
	static const string UTIL_SCRIPT_NAME;
	static const string VARS_SCRIPT_NAME;
	static const string VERB_SCRIPT_NAME;

	string _name;
	string _description;
	uint8_t _key;
	vector<Array *> _arrays;
	vector<Room *> _rooms;
	vector<Object *> _objects;
	vector<Script *> _scripts;
	vector<Midi *> _midis;
	vector<Costume *> _costumes;
	vector<Charset *> _charsets;
	vector<Voice *> _voices;
	vector<Declaration *> _declarations;
	vector<Function *> _functions;

	void loadRooms(string dirPath, XMLNode *node);
	void loadObjects(string dirPath, XMLNode *node);
	void loadMidis(string dirPath, XMLNode *node);
	void loadCostumes(string dirPath, XMLNode *node);
	void loadScripts(string dirPath, XMLNode *node);
	void loadCharsets(string dirPath, XMLNode *node);
	void loadVoices(string dirPath, XMLNode *node);
	void saveRooms(string dirPath, XMLNode *node);
	void saveObjects(string dirPath, XMLNode *node);
	void saveMidis(string dirPath, XMLNode *node);
	void saveCostumes(string dirPath, XMLNode *node);
	void saveScripts(string dirPath, XMLNode *node);
	void saveCharsets(string dirPath, XMLNode *node);
	void saveVoices(string dirPath, XMLNode *node);
	void prepare();
	void parse(string programDirPath);
	void parseLibScumm(string programDirPath);
	void compile();
	void generate(string outputDirPath);
public:
	static const uint8_t N_DEFAULT_ACTORS;
	static const uint16_t MAX_WORD_VARIABLES;
	static const uint8_t MAX_LOCAL_VARIABLES;

	Game();
	void load(string dirPath);
	void save(string dirPath);
	void build(string programDirPath, string outputDirPath);
	string getName() { return _name; }
	string getDescription() { return _description; }
	uint8_t getKey() { return _key; }
	uint16_t getNumberOfArrays() { return _arrays.size(); }
	Array *getArray(uint16_t index) { return _arrays[index]; }
	uint8_t getNumberOfRooms() { return _rooms.size(); }
	Room *getRoom(uint8_t index) { return _rooms[index]; }
	uint16_t getNumberOfObjects() { return _objects.size(); }
	Object *getObject(uint16_t index) { return _objects[index]; }
	uint16_t getNumberOfMidis() { return _midis.size(); }
	Midi *getMidi(uint16_t index) { return _midis[index]; }
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
