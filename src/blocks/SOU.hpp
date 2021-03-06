#ifndef _SOU_BLOCK_HPP_
#define _SOU_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Midi;
class GMD;

class SOU
{
private:
	GMD *_gmd;
public:
	SOU(Midi *midi);
	uint32_t getSize();
	void write(fstream &f);
	~SOU();
};

#endif
