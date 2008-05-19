#ifndef _DSCR_BLOCK_HPP_
#define _DSCR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class LECF;

class DSCR
{
private:
	uint16_t _nItems;
	vector<uint8_t> _ids;
	vector<uint32_t> _offsets;

	uint32_t getSize();
public:
	DSCR(Game *game, LECF *lecf);
	void write(ofstream &f);
	~DSCR();
};

#endif

