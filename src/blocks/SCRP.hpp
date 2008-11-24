#ifndef _SCRP_BLOCK_HPP_
#define _SCRP_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Function;

class SCRP
{
private:
	uint32_t _size;
	vector<uint8_t> _bytes;
public:
	SCRP(Function *function);
	uint32_t getSize();
	void write(fstream &f);
	~SCRP();
};

#endif

