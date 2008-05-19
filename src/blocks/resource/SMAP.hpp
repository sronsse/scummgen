#ifndef _SMAP_BLOCK_HPP_
#define _SMAP_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Image;

class SMAP
{
private:
	static const uint8_t STRIP_WIDTH;
	static const uint8_t CID_NO_COMPRESSION;

	uint16_t _nStrips;
	uint16_t _height;
	vector<vector<uint8_t> > _strips;
	vector<uint32_t> _offsets;
public:
	SMAP(Image *image);
	uint32_t getSize();
	void write(ofstream &f);
	~SMAP();
};

#endif

