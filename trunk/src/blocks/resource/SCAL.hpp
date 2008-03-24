#ifndef _SCAL_BLOCK_HPP_
#define _SCAL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Map;

class SCAL
{
private:
	vector<uint32_t> _s1s;
	vector<uint32_t> _y1s;
	vector<uint32_t> _s2s;
	vector<uint32_t> _y2s;
public:
	SCAL(Map *map);
	uint32_t getSize();
	void write(ofstream &f);
	~SCAL();
};

#endif

