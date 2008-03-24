#ifndef _MAP_BLOCK_HPP_
#define _MAP_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class FRMT;

class MAP
{
private:
	uint32_t _size;
	FRMT *_frmt;
public:
	MAP(ifstream &f);
	uint32_t getSize();
	void write(ofstream &f);
	~MAP();
};

#endif

