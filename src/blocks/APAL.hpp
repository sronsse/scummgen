#ifndef _APAL_BLOCK_HPP_
#define _APAL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Palette;

class APAL
{
private:
	static const uint16_t N_COLORS;

	vector<uint8_t> _rs;
	vector<uint8_t> _gs;
	vector<uint8_t> _bs;
public:
	APAL(Palette *palette);
	uint32_t getSize();
	void write(fstream &f);
	~APAL();
};

#endif

