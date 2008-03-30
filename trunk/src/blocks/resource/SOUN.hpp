#ifndef _SOUN_BLOCK_HPP_
#define _SOUN_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Sound;
class VOC;

class SOUN
{
private:
	uint32_t _size;
	VOC *_voc;
public:
	SOUN(Sound *sound);
	uint32_t getSize();
	void write(ofstream &f);
	~SOUN();
};

#endif

