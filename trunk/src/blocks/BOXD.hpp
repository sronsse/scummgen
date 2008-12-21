#ifndef _BOXD_BLOCK_HPP_
#define _BOXD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Map;

class BOXD
{
private:
	static const uint16_t FAKE_VALUE;
	static const uint8_t FAKE_MASK;
	static const uint8_t FAKE_FLAGS;
	static const uint8_t FAKE_SCALE;

	uint8_t _nBoxes;
	vector<int16_t> _ulxs, _ulys;
	vector<int16_t> _urxs, _urys;
	vector<int16_t> _lrxs, _lrys;
	vector<int16_t> _llxs, _llys;
	vector<uint8_t> _masks;
	vector<uint8_t> _flags;
	vector<uint16_t> _scales;
public:
	BOXD(Map *map);
	uint32_t getSize();
	void write(fstream &f);
	~BOXD();
};

#endif

