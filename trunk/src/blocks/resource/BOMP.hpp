#ifndef _BOMP_BLOCK_HPP_
#define _BOMP_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Image;
class WRAP;

class BOMP
{
private:
	uint32_t _size;
	uint32_t _width;
	uint32_t _height;
	vector<uint16_t> _lengths;
	vector<vector<uint8_t> > _lines;
public:
	BOMP(Image *image);
	void writeLine(vector<uint8_t> &line, Image *image, uint32_t y);
	uint32_t getSize();
	void write(ofstream &f);
	~BOMP();
};

#endif

