#ifndef _AARY_BLOCK_HPP_
#define _AARY_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class AARY
{
private:
	uint32_t _size;
	vector<uint32_t> _arrayIDs;
	vector<uint32_t> _arrayDimAs;
	vector<uint32_t> _arrayDimBs;

	uint32_t getSize();
public:
	AARY(ifstream &f);
	void write(ofstream &f);
	~AARY();
};

#endif

