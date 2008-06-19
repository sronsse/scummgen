#ifndef _DSOU_BLOCK_HPP_
#define _DSOU_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class LECF;

class DSOU
{
private:
	uint16_t _nItems;
	vector<uint8_t> _ids;
	vector<uint32_t> _offsets;

	uint32_t getSize();
public:
	DSOU(Game *game, LECF *lecf);
	void write(fstream &f);
	~DSOU();
};

#endif

