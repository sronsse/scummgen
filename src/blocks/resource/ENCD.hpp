#ifndef _ENCD_BLOCK_HPP_
#define _ENCD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Script;

class ENCD
{
private:
	vector<uint8_t> _bytes;
public:
	ENCD(Script *script);
	uint32_t getSize();
	void write(fstream &f);
	~ENCD();
};

#endif

