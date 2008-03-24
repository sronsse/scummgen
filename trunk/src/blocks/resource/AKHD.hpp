#ifndef _AKHD_BLOCK_HPP_
#define _AKHD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Costume;

class AKHD
{
private:
	static const uint8_t N_DIRECTIONS_DIVIDER;
	static const uint16_t UNKNOWN1;
	static const uint8_t UNKNOWN2;
	static const uint16_t UNKNOWN3;

	uint8_t _flags;
	uint16_t _nAnims;
	uint16_t _nFrames;
	uint16_t _codec;
public:
	AKHD(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~AKHD();
};

#endif

