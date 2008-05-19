#ifndef _NLSC_BLOCK_HPP_
#define _NLSC_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Room;

class NLSC
{
private:
	uint8_t _nLocalScripts;
public:
	NLSC(Room *room);
	uint32_t getSize();
	void write(ofstream &f);
	~NLSC();
};

#endif

