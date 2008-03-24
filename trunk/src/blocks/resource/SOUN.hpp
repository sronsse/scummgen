#ifndef _SOUN_BLOCK_HPP_
#define _SOUN_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class iMUS;

class SOUN
{
private:
	uint32_t _size;
	iMUS *_imus;
public:
	SOUN(ifstream &f);
	uint32_t getSize();
	void write(ofstream &f);
	~SOUN();
};

#endif

