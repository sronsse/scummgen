#ifndef _RGBS_BLOCK_HPP_
#define _RGBS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class RGBS
{
private:
	uint32_t _size;
	vector<uint8_t> _rs;
	vector<uint8_t> _gs;
	vector<uint8_t> _bs;
public:
	RGBS(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~RGBS();
};

#endif

