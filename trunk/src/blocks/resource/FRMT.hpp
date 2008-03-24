#ifndef _FRMT_BLOCK_HPP_
#define _FRMT_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class FRMT
{
private:
	uint32_t _size;
public:
	FRMT(ifstream &f);
	uint32_t getSize();
	void write(ofstream &f);
	~FRMT();
};

#endif

