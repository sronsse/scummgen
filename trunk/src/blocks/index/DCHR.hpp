#ifndef _DCHR_BLOCK_HPP_
#define _DCHR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class DCHR
{
private:
	uint32_t _size;
	uint32_t _nItems;
	vector<uint8_t> _ids;
	vector<uint32_t> _offsets;

	uint32_t getSize();
public:
	DCHR(ifstream &f);
	void write(ofstream &f);
	~DCHR();
};

#endif

