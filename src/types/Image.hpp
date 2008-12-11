#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <stdint.h>
#include <string>
#include <vector>
#include "util/BMPFile.hpp"
using namespace std;

class ZPlane
{
private:
	uint16_t _width;
	uint16_t _height;
	vector<vector<uint8_t> > _pixels;
public:
	ZPlane(string fileName);
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	uint8_t getPixel(uint32_t x, uint32_t y) { return _pixels[x][y]; }
	~ZPlane();
};

class Image
{
private:
	uint16_t _width;
	uint16_t _height;
	vector<Color> _colors;
	vector<vector<uint8_t> > _pixels;
	vector<ZPlane *> _zPlanes;
	uint8_t _paletteBaseIndex;
public:
	Image(string dirName, string fileName, uint16_t nZPlanes);
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	uint16_t getNumberOfColors() { return _colors.size(); }
	Color getColor(uint8_t index) { return _colors[index]; }
	uint8_t getPixel(uint32_t x, uint32_t y) { return _pixels[x][y] == 0 ? 0 : _pixels[x][y] + _paletteBaseIndex; }
	uint16_t getNumberOfZPlanes() { return _zPlanes.size(); }
	ZPlane *getZPlane(uint16_t index) { return _zPlanes[index]; }
	void setPaletteBaseIndex(uint8_t paletteBaseIndex) { _paletteBaseIndex = paletteBaseIndex; }
	~Image();
};

#endif

