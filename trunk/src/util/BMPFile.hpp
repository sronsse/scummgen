#ifndef _BMPFILE_HPP_
#define _BMPFILE_HPP_

#include <string>
#include <vector>
using namespace std;

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Color;

class BMPFile
{
private:
	static const uint8_t BI_RGB;

	uint32_t _width;
	uint32_t _height;
	uint16_t _bpp;
	vector<Color> _colors;
	vector<vector<uint8_t> > _pixels;
public:
	BMPFile();
	bool open(string fileName);
	uint32_t getWidth() { return _width; }
	uint32_t getHeight() { return _height; }
	uint16_t getBPP() { return _bpp; }
	uint32_t getNumberOfColors() { return _colors.size(); }
	Color getColor(uint32_t index) { return _colors[index]; }
	uint8_t getPixel(uint32_t x, uint32_t y) { return _pixels[x][y]; }
	~BMPFile();
};

#endif

