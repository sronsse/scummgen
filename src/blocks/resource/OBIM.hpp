#ifndef _OBIM_BLOCK_HPP_
#define _OBIM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Object;
class IMHD;
class IMxx;

class OBIM
{
private:
	IMHD *_imhd;
	vector<IMxx *> _imxxs;
public:
	OBIM(Object *object);
	uint32_t getSize();
	void write(fstream &f);
	~OBIM();
};

#endif

