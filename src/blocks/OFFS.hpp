#ifndef _OFFS_BLOCK_HPP_
#define _OFFS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class APAL;

class OFFS
{
private:
	vector<uint32_t> _offsets;
public:
	OFFS(vector<APAL *> apals);
	uint32_t getSize();
	void write(fstream &f);
	~OFFS();
};

#endif

