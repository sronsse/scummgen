#ifndef _DROO_BLOCK_HPP_
#define _DROO_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;

class DROO
{
private:
	uint32_t _nItems;
	vector<uint8_t> _ids;
	vector<uint32_t> _offsets;

	uint32_t getSize();
public:
	DROO(Game *game);
	void write(ofstream &f);
	~DROO();
};

#endif

