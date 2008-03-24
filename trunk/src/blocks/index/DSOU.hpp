#ifndef _DSOU_BLOCK_HPP_
#define _DSOU_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class DSOU
{
private:
	uint32_t _size;
	uint32_t _nItems;
	vector<uint8_t> _ids;
	vector<uint32_t> _offsets;

	uint32_t getSize();
public:
	DSOU(ifstream &f);
	void write(ofstream &f);
	~DSOU();
};

#endif

