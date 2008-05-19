#ifndef _DOBJ_BLOCK_HPP_
#define _DOBJ_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;

class DOBJ
{
private:
	static const uint8_t N_CHARS;

	uint32_t _nObjects;
	vector<string> _objectNames;
	vector<uint8_t> _objectStates;
	vector<uint8_t> _objectRooms;
	vector<uint32_t> _classData;

	uint32_t getSize();
public:
	DOBJ(Game *game);
	void write(ofstream &f);
	~DOBJ();
};

#endif

