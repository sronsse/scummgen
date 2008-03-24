#ifndef _OBIM_BLOCK_HPP_
#define _OBIM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Object;
class IMHD;
class IMAG;

class OBIM
{
private:
	IMHD *_imhd;
	IMAG *_imag;
public:
	OBIM(Object *object);
	uint32_t getSize();
	void write(ofstream &f);
	~OBIM();
};

#endif

