#ifndef _SMAP_BLOCK_HPP_
#define _SMAP_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Image;
class BSTR;
class ZPLN;

class SMAP
{
private:
	uint32_t _size;
	BSTR *_bstr;
	ZPLN *_zpln;
public:
	SMAP(Image *image);
	uint32_t getSize();
	void write(ofstream &f);
	~SMAP();
};

#endif

