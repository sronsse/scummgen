#ifndef _WRAP5_BLOCK_HPP_
#define _WRAP5_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class OFFS;

class WRAP5
{
private:
	static const uint8_t STRIP_WIDTH;

	uint32_t _size;
	OFFS *_offs;
	uint32_t _width;
	uint32_t _height;
	uint8_t **_zPlane;
public:
	WRAP5(ifstream &f, uint32_t width, uint32_t height);
	void readStrip(ifstream &f, uint8_t **strip);
	uint32_t getSize();
	void write(ofstream &f);
	~WRAP5();
};

#endif

