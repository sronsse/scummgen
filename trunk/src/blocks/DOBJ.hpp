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
	uint16_t _nItems;
	vector<uint8_t> _ownersAndStates;
	vector<uint32_t> _classData;

	uint32_t getSize();
public:
	DOBJ(Game *game);
	void write(fstream &f);
	~DOBJ();
};

#endif

