#ifndef _DRSC_BLOCK_HPP_
#define _DRSC_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class LECF;

class DRSC
{
private:
	uint32_t _nItems;
	vector<uint8_t> _ids;
	vector<uint32_t> _offsets;

	uint32_t getSize();
public:
	DRSC(Game *game, LECF *lecf);
	void write(ofstream &f);
	~DRSC();
};

#endif

