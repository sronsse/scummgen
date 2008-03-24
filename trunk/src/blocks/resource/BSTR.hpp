#ifndef _BSTR_BLOCK_HPP_
#define _BSTR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Image;
class WRAP3;

class BSTR
{
private:
	uint32_t _size;
	WRAP3 *_wrap;
public:
	BSTR(Image *image);
	uint32_t getSize();
	void write(ofstream &f);
	~BSTR();
};

#endif

