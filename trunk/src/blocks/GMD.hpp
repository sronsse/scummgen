#ifndef _GMD_BLOCK_HPP_
#define _GMD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Midi;

class GMD
{
private:
	vector<uint8_t> _dataBytes;
public:
	GMD(Midi *midi);
	uint32_t getSize();
	void write(fstream &f);
	~GMD();
};

#endif
