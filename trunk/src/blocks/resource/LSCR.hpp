#ifndef _LSCR_BLOCK_HPP_
#define _LSCR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Script;

class LSCR
{
private:
	vector<uint8_t> _bytes;
public:
	LSCR(Script *script);
	uint32_t getSize();
	void write(ofstream &f);
	~LSCR();
};

#endif

