#ifndef _OBNA_BLOCK_HPP_
#define _OBNA_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
using namespace std;

class Object;

class OBNA
{
private:
	string _name;
public:
	OBNA(Object *object);
	uint32_t getSize();
	void write(fstream &f);
	~OBNA();
};

#endif

