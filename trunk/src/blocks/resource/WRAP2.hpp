#ifndef _WRAP2_BLOCK_HPP_
#define _WRAP2_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Image;
class Object;
class OFFS;
class SMAP;
class BOMP;
class WRAP;

class WRAP2
{
private:
	OFFS *_offs;
	vector<SMAP *> _smaps;
	vector<BOMP *> _bomps;
public:
	WRAP2(Image *image);
	WRAP2(Object *object);
	uint32_t getSize();
	void write(ofstream &f);
	~WRAP2();
};

#endif

