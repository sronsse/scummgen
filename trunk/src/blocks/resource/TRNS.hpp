#ifndef _TRNS_BLOCK_HPP_
#define _TRNS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Palette;

class TRNS
{
private:
	uint8_t _transparentIndex;
public:
	TRNS(Palette *palette);
	uint32_t getSize();
	void write(ofstream &f);
	~TRNS();
};

#endif

