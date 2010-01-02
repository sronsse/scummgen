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
	static const uint8_t FLAGS;
	static const uint8_t PARENT;
	static const uint8_t ACTOR_DIR;

	uint16_t _id;
	uint16_t _x;
	uint16_t _y;
	uint16_t _width;
	uint16_t _height;
public:
	CDHD(Object *object);
	uint32_t getSize();
	void write(fstream &f);
	~CDHD();
};

#endif
