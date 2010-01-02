#ifndef _IMHD_BLOCK_HPP_
#define _IMHD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Object;

class IMHD
{
private:
	static const uint16_t UNKNOWN;
	static const uint16_t X;
	static const uint16_t Y;

	uint16_t _id;
	uint16_t _nImages;
	uint32_t _nZPlanesPerImage;
	uint16_t _width;
	uint16_t _height;
	vector<int16_t> _hotspotXs;
	vector<int16_t> _hotspotYs;
public:
	IMHD(Object *object);
	uint32_t getSize();
	void write(fstream &f);
	~IMHD();
};

#endif
