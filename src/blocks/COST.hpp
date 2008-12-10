#ifndef _COST_BLOCK_HPP_
#define _COST_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;
class Frame;

class COST
{
private:
	static const uint32_t UNKNOWN;
	static const uint8_t N_LIMBS;
	static const uint16_t LIMB_MASK;
	static const uint8_t REDIR_LIMB;
	static const uint8_t REDIR_PICT;

	uint8_t _format;
	vector<uint8_t> _palette;
	uint16_t _animCmdsOffset;
	vector<uint16_t> _limbsOffsets;
	vector<uint16_t> _animsOffsets;
	vector<uint16_t> _animStarts;
	vector<uint8_t> _animNoLoopAndEndOffsets;
	vector<uint8_t> _animCmds;
	vector<uint16_t> _pictOffsets;
	vector<uint16_t> _pictWidths;
	vector<uint16_t> _pictHeights;
	vector<int16_t> _pictXs;
	vector<int16_t> _pictYs;
	vector<int16_t> _pictXIncs;
	vector<int16_t> _pictYIncs;
	vector<vector<uint8_t> > _dataBytes;

	void getDataBytes(Costume *costume, Frame *frame, vector<uint8_t> &dataBytes);
public:
	COST(Costume *costume);
	uint32_t getSize();
	void write(fstream &f);
	~COST();
};

#endif
