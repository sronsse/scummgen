#ifndef _RMHD_BLOCK_HPP_
#define _RMHD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Room;

class RMHD
{
private:
	uint16_t _width;
	uint16_t _height;
	uint16_t _nObjects;
public:
	RMHD(Room *room);
	uint32_t getSize();
	void write(fstream &f);
	~RMHD();
};

#endif

