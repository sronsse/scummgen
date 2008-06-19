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
	static const uint32_t UNKNOWN;

	uint32_t _nBoxes;
	vector<int32_t> _ulxs, _ulys;
	vector<int32_t> _urxs, _urys;
	vector<int32_t> _lrxs, _lrys;
	vector<int32_t> _llxs, _llys;
	vector<uint32_t> _masks;
	vector<uint32_t> _flags;
	vector<uint32_t> _scaleSlots;
	vector<uint32_t> _scales;
public:
	BOXD(Map *map);
	uint32_t getSize();
	void write(fstream &f);
	~BOXD();
};

#endif

