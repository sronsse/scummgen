#ifndef _RMIM_BLOCK_HPP_
#define _RMIM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Image;
class RMIH;
class IMxx;

class RMIM
{
private:
	RMIH *_rmih;
	IMxx *_im00;
public:
	RMIM(Image *roomImage);
	uint32_t getSize();
	void write(fstream &f);
	~RMIM();
};

#endif

