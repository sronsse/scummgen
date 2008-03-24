#ifndef _RMHD_BLOCK_HPP_
#define _RMHD_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
using namespace std;

class Room;

class RMHD
{
private:
	static const uint16_t VERSION;

	uint32_t _width;
	uint32_t _height;
	uint32_t _nObjects;
	uint32_t _nZPlanes;
	uint32_t _transparentIndex;
public:
	RMHD(Room *room);
	uint32_t getSize();
	void write(ofstream &f);
	~RMHD();
};

#endif

