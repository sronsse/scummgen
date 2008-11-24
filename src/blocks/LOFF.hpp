#ifndef _LOFF_BLOCK_HPP_
#define _LOFF_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class LFLF;

class LOFF
{
private:
	uint8_t _nRooms;
	vector<uint8_t> _roomIDs;
	vector<uint32_t> _roomOffsets;
public:
	LOFF(Game *game, vector<LFLF *> lflfs);
	uint32_t getSize();
	void write(fstream &f);
	~LOFF();
};

#endif

