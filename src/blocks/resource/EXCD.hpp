#ifndef _EXCD_BLOCK_HPP_
#define _EXCD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Script;

class EXCD
{
private:
	vector<uint8_t> _bytes;
public:
	EXCD(Script *script);
	uint32_t getSize();
	void write(fstream &f);
	~EXCD();
};

#endif

