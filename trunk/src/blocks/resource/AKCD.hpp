#ifndef _AKCD_BLOCK_HPP_
#define _AKCD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class AKCD
{
private:
	vector<uint16_t> _lengths;
	vector<vector<uint8_t> > _lines;
	vector<uint32_t> _offsets;
public:
	AKCD(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	uint32_t getOffset(uint32_t index) { return _offsets[index]; }
	~AKCD();
};

#endif

