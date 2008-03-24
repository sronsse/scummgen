#ifndef _BOXM_BLOCK_HPP_
#define _BOXM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class BOXM
{
private:
	uint32_t _size;
	vector<uint8_t> _boxAs;
	vector<uint8_t> _boxBs;
	vector<uint8_t> _dests;
public:
	BOXM(ifstream &f);
	uint32_t getSize();
	void write(ofstream &f);
	~BOXM();
};

#endif

