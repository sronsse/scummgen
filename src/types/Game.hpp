#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Room;
class Voice;

class Game
{
private:
	string _longName;
	string _shortName;
	vector<Room *> _rooms;
	vector<Voice *> _voices;
public:
	Game(string dirName);
	string getLongName() { return _longName; }
	string getShortName() { return _shortName; }
	uint8_t getNumberOfRooms() { return _rooms.size(); }
	Room *getRoom(uint8_t index) { return _rooms[index]; }
	uint16_t getNumberOfVoices() { return _voices.size(); }
	Voice *getVoice(uint16_t index) { return _voices[index]; }
	~Game();
};

#endif

