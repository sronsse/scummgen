#ifndef _LSCR_BLOCK_HPP_
#define _LSCR_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Function;

class LSCR
{
private:
	uint8_t _id;
	vector<uint8_t> _bytes;
public:
	LSCR(Function *function);
	uint32_t getSize();
	void write(fstream &f);
	~LSCR();
};

#endif

