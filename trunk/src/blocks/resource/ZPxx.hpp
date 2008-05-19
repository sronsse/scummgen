#ifndef _ZPxx_BLOCK_HPP_
#define _ZPxx_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class ZPlane;

class ZPxx
{
private:
	uint8_t _index;
public:
	ZPxx(ZPlane *zPlane, uint8_t index);
	uint32_t getSize();
	void write(ofstream &f);
	~ZPxx();
};

#endif

