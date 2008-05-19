#ifndef _IMXX_BLOCK_HPP_
#define _IMXX_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Image;
class SMAP;
class ZPxx;

class IMxx
{
private:
	uint8_t _index;
	SMAP *_smap;
	vector<ZPxx *> _zpxxs;
public:
	IMxx(Image *image, uint8_t index);
	uint32_t getSize();
	void write(ofstream &f);
	~IMxx();
};

#endif

