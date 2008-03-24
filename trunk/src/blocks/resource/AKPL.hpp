#ifndef _AKPL_BLOCK_HPP_
#define _AKPL_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;

class AKPL
{
private:
	static const uint8_t N_CHANNELS;

	vector<uint8_t> _palette;
public:
	AKPL(Costume *costume);
	uint32_t getSize();
	void write(ofstream &f);
	~AKPL();
};

#endif

