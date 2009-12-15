#ifndef _APAL_BLOCK_HPP_
#define _APAL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
#include "util/BMPFile.hpp"
using namespace std;

class Palette;

class APAL
{
private:
	vector<Color> _colors;
public:
	APAL(Palette *globalPalette, Palette *localPalette);
	uint32_t getSize();
	void write(fstream &f);
	~APAL();
};

#endif

