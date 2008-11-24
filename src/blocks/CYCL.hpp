#ifndef _CYCL_BLOCK_HPP_
#define _CYCL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Palette;

class CYCL
{
private:
	static const uint16_t FREQUENCY;
	static const uint16_t FORWARD;
	static const uint16_t BACKWARD;
	static const uint16_t UNKNOWN;

    vector<uint16_t> _ids;
    vector<uint16_t> _freqs;
    vector<uint16_t> _flags;
    vector<uint8_t> _starts;
    vector<uint8_t> _ends;
public:
	CYCL(Palette *palette);
	uint32_t getSize();
	void write(fstream &f);
	~CYCL();
};

#endif

