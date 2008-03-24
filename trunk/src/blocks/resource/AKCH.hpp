#ifndef _AKCH_BLOCK_HPP_
#define _AKCH_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class AKCH
{
private:
	static const uint8_t MAX_LIMBS;
	static const uint8_t MODE_SINGLE_FRAME;
	static const uint8_t MODE_STOP_LIMB;
	static const uint8_t MODE_START_LIMB;

	uint32_t _size;
	vector<uint16_t> _offsets;
	vector<uint16_t> _limbMasks;
	vector<vector<uint8_t> > _modes;
	vector<vector<uint16_t> > _starts;
	vector<vector<uint16_t> > _lengths;
public:
	AKCH(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~AKCH();
};

#endif

