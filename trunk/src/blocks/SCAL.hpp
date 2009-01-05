#ifndef _SCAL_BLOCK_HPP_
#define _SCAL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Map;

class SCAL
{
private:
	static const uint8_t N_SLOTS;
	static const uint8_t DEFAULT_SCALE;
	static const uint8_t DEFAULT_Y1;
	static const uint8_t DEFAULT_Y2;

	vector<uint16_t> _s1s;
	vector<uint16_t> _y1s;
	vector<uint16_t> _s2s;
	vector<uint16_t> _y2s;
public:
	SCAL(Map *map);
	uint32_t getSize();
	void write(fstream &f);
	~SCAL();
};

#endif
