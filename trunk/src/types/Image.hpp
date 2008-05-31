#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class ZPlane
{
private:
	uint16_t _width;
	uint16_t _height;
	vector<vector<uint8_t> > _pixels;
public:
	ZPlane(string fileName);
	~ZPlane();
};

class Image
{
private:
	uint16_t _width;
	uint16_t _height;
	vector<vector<uint8_t> > _pixels;
	vector<ZPlane *> _zPlanes;
public:
	Image(string dirName, string fileName, uint16_t nZPlanes);
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	uint8_t getPixel(uint32_t x, uint32_t y) { return _pixels[x][y]; }
	uint16_t getNumberOfZPlanes() { return _zPlanes.size(); }
	ZPlane *getZPlane(uint16_t index) { return _zPlanes[index]; }
	~Image();
};

#endif

