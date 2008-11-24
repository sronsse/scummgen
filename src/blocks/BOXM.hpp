#ifndef _BOXM_BLOCK_HPP_
#define _BOXM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Map;

class BOXM
{
private:
	static const uint8_t BOX_END;

	vector<vector<uint8_t> > _boxAs;
	vector<vector<uint8_t> > _boxBs;
	vector<vector<uint8_t> > _dests;
public:
	BOXM(Map *map);
	uint32_t getSize();
	void write(fstream &f);
	~BOXM();
};

#endif

