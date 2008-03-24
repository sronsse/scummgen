#ifndef _CDHD_BLOCK_HPP_
#define _CDHD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Object;

class CDHD
{
private:
	static const uint32_t VERSION;

	uint16_t _id;
	uint8_t _parent;
	uint8_t _parentState;
public:
	CDHD(Object *object);
	uint32_t getSize();
	void write(ofstream &f);
	~CDHD();
};

#endif

