#ifndef _BOXM_BLOCK_HPP_
#define _BOXM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class BOXM
{
private:
	static const uint8_t BOX_END;

	vector<vector<uint8_t> > _from;
	vector<vector<uint8_t> > _to;
	vector<vector<uint8_t> > _dests;
public:
	BOXM();
	uint32_t getSize();
	void write(fstream &f);
	~BOXM();
};

#endif
