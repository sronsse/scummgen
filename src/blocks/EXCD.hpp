#ifndef _EXCD_BLOCK_HPP_
#define _EXCD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Function;

class EXCD
{
private:
	vector<uint8_t> _bytes;
public:
	EXCD(Function *function);
	uint32_t getSize();
	void write(fstream &f);
	~EXCD();
};

#endif

