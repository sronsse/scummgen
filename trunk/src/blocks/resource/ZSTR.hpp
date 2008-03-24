#ifndef _ZSTR_BLOCK_HPP_
#define _ZSTR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class WRAP5;

class ZSTR
{
private:
	uint32_t _size;
	WRAP5 *_wrap;
public:
	ZSTR(ifstream &f, uint32_t width, uint32_t height);
	uint32_t getSize();
	void write(ofstream &f);
	~ZSTR();
};

#endif

