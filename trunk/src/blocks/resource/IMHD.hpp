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
	static const uint8_t N_CHARS;
	static const uint32_t VERSION;
	static const uint32_t UNKNOWN1;
	static const uint32_t UNKNOWN2;
	static const uint32_t UNKNOWN3;
	static const uint32_t UNKNOWN4;

	string _name;
	uint32_t _nImages;
	uint32_t _x;
	uint32_t _y;
	uint32_t _width;
	uint32_t _height;
	vector<int32_t> _hotSpotXs;
	vector<int32_t> _hotSpotYs;
public:
	IMHD(Object *object);
	uint32_t getSize();
	void write(ofstream &f);
	~IMHD();
};

#endif

