#ifndef _WRAP_BLOCK_HPP_
#define _WRAP_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Palette;
class OFFS;
class APAL;

class WRAP
{
private:
	OFFS *_offs;
	vector<APAL *> _apals;
public:
	WRAP(Palette *globalPalette, Palette *localPalette);
	uint32_t getSize();
	void write(fstream &f);
	~WRAP();
};

#endif

