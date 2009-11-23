#ifndef _TRNS_BLOCK_HPP_
#define _TRNS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Palette;

class TRNS
{
private:
	static const uint8_t TRANSPARENT_INDEX;
public:
	TRNS(Palette *palette);
	uint32_t getSize();
	void write(fstream &f);
	~TRNS();
};

#endif

