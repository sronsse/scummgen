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
	static const uint8_t OWNER_AND_STATE;
	static const uint32_t CLASS_DATA;

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
