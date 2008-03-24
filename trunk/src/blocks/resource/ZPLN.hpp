#ifndef _ZPLN_BLOCK_HPP_
#define _ZPLN_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class WRAP4;

class ZPLN
{
private:
	uint32_t _size;
	WRAP4 *_wrap;
public:
	ZPLN(ifstream &f, uint32_t width, uint32_t height);
	uint32_t getSize();
	void write(ofstream &f);
	~ZPLN();
};

#endif

