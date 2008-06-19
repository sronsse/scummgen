#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Room;
class Script;
class Charset;
class Voice;

class Game
{
private:
	string _longName;
	string _shortName;
	uint8_t _key;
	vector<Room *> _rooms;
	vector<Script *> _scripts;
	vector<Charset *> _charsets;
	vector<Voice *> _voices;

	void loadRooms(string dirName);
	void loadScripts(string dirName);
	void loadCharsets(string dirName);
	void loadVoices(string dirName);
public:
	Game(string dirName);
	string getLongName() { return _longName; }
	string getShortName() { return _shortName; }
	uint8_t getKey() { return _key; }
	uint8_t getNumberOfRooms() { return _rooms.size(); }
	Room *getRoom(uint8_t index) { return _rooms[index]; }
	uint8_t getNumberOfScripts() { return _scripts.size(); }
	Script *getScript(uint8_t index) { return _scripts[index]; }
	uint8_t getNumberOfCharsets() { return _charsets.size(); }
	Charset *getCharset(uint8_t index) { return _charsets[index]; }
	uint16_t getNumberOfVoices() { return _voices.size(); }
	Voice *getVoice(uint16_t index) { return _voices[index]; }
	~Game();
};

#endif

