#ifndef _SOUN_BLOCK_HPP_
#define _SOUN_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Midi;
class SOU;

class SOUN
{
private:
	SOU *_sou;
public:
	SOUN(Midi *midi);
	uint32_t getSize();
	void write(fstream &f);
	~SOUN();
};

#endif
