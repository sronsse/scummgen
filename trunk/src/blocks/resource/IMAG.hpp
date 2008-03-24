#ifndef _IMAG_BLOCK_HPP_
#define _IMAG_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
using namespace std;

class Image;
class Object;
class WRAP2;

class IMAG
{
private:
	WRAP2 *_wrap;
public:
	IMAG(Image *image);
	IMAG(Object *object);
	uint32_t getSize();
	void write(ofstream &f);
	~IMAG();
};

#endif

