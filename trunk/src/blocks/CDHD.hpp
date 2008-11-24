#ifndef _CDHD_BLOCK_HPP_
#define _CDHD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Object;

class CDHD
{
private:
	static const uint16_t UNKNOWN_1;
	static const uint16_t UNKNOWN_2;
	uint16_t _id;
	uint8_t _x;
	uint8_t _y;
	uint8_t _width;
	uint8_t _height;
	uint8_t _flags;
	uint8_t _parent;
	uint16_t _walkX;
	uint16_t _walkY;
	uint8_t _actorDir;
public:
	CDHD(Object *object);
	uint32_t getSize();
	void write(fstream &f);
	~CDHD();
};

#endif

