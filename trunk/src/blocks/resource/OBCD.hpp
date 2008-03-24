#ifndef _OBCD_BLOCK_HPP_
#define _OBCD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Object;
class CDHD;
class OBNA;
class VERB;

class OBCD
{
private:
	uint32_t _size;
	CDHD *_cdhd;
	OBNA *_obna;
	VERB *_verb;
public:
	OBCD(Object *object);
	uint32_t getSize();
	void write(ofstream &f);
	~OBCD();
};

#endif

