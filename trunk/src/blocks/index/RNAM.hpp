#ifndef _RNAM_BLOCK_HPP_
#define _RNAM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Game;

class RNAM
{
private:
	static const uint8_t N_CHARS;
	static const uint8_t XOR_VALUE;

	vector<uint8_t> _roomIDs;
	vector<string> _roomNames;

	uint32_t getSize();
public:
	RNAM(Game *game);
	void write(ofstream &f);
	~RNAM();
};

#endif
