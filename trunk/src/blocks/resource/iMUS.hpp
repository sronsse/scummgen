#ifndef _IMUS_BLOCK_HPP_
#define _IMUS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class MAP;

class iMUS
{
private:
	uint32_t _size;
	MAP *_map;
public:
	iMUS(ifstream &f);
	uint32_t getSize();
	void write(ofstream &f);
	~iMUS();
};

#endif

