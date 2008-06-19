#ifndef _COST_BLOCK_HPP_
#define _COST_BLOCK_HPP_

#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class COST
{
private:
public:
	COST(Costume *costume);
	uint32_t getSize();
	void write(fstream &f);
	~COST();
};

#endif

