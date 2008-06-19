#ifndef _RMIH_BLOCK_HPP_
#define _RMIH_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Image;

class RMIH
{
private:
	uint16_t _nZPlanes;
public:
	RMIH(Image *image);
	uint32_t getSize();
	void write(fstream &f);
	~RMIH();
};

#endif

