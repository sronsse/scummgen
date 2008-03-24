#ifndef _WRAP4_BLOCK_HPP_
#define _WRAP4_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class OFFS;
class ZSTR;

class WRAP4
{
private:
	uint32_t _size;
	OFFS *_offs;
	vector<ZSTR *> _zstrs;
public:
	WRAP4(ifstream &f, uint32_t width, uint32_t height);
	uint32_t getSize();
	void write(ofstream &f);
	~WRAP4();
};

#endif

