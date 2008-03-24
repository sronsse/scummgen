#ifndef _AKSQ_BLOCK_HPP_
#define _AKSQ_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class AKSQ
{
private:
	uint32_t _size;
	vector<uint8_t> _commands;
public:
	AKSQ(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~AKSQ();
};

#endif

