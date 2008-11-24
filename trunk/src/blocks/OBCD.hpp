#ifndef _OBCD_BLOCK_HPP_
#define _OBCD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Object;
class CDHD;
class VERB;
class OBNA;

class OBCD
{
private:
	CDHD *_cdhd;
	VERB *_verb;
	OBNA *_obna;
public:
	OBCD(Object *object);
	uint32_t getSize();
	void write(fstream &f);
	~OBCD();
};

#endif

