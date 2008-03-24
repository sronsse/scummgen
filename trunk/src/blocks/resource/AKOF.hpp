#ifndef _AKOF_BLOCK_HPP_
#define _AKOF_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Costume;
class AKCD;

class AKOF
{
private:
	vector<uint32_t> _akcdOffsets;
	vector<uint16_t> _akciOffsets;
public:
	AKOF(Costume *costume, AKCD *akcd);
	uint32_t getSize();
	void write(ofstream &f);
	~AKOF();
};

#endif

