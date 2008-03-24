#ifndef _OFFS_BLOCK_HPP_
#define _OFFS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class APAL;
class SMAP;
class BOMP;

class OFFS
{
private:
	vector<uint32_t> _offsets;
public:
	OFFS(vector<APAL *> apals);
	OFFS(vector<SMAP *> smaps, vector<BOMP *> bomps);
	OFFS(vector<vector<uint8_t> > strips);
	uint32_t getSize();
	void write(ofstream &f);
	~OFFS();
};

#endif

