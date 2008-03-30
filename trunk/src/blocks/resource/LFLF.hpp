#ifndef _LFLF_BLOCK_HPP_
#define _LFLF_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Room;
class ROOM;
class RMSC;
class SCRP;
class SOUN;
class AKOS;

class LFLF
{
private:
	uint32_t _size;
	ROOM *_room;
	RMSC *_rmsc;
	vector<SCRP *> _scrps;
	vector<SOUN *> _souns;
	vector<AKOS *> _akoss;
	uint32_t _rmscOffset;
	vector<uint32_t> _scrpOffsets;
	vector<uint32_t> _sounOffsets;
	vector<uint32_t> _akosOffsets;
public:
	LFLF(Room *room);
	uint32_t getSize();
	uint32_t getRMSCOffset() { return _rmscOffset; }
	uint32_t getSCRPOffset(uint32_t index) { return _scrpOffsets[index]; }
	uint32_t getSOUNOffset(uint32_t index) { return _sounOffsets[index]; }
	uint32_t getAKOSOffset(uint32_t index) { return _akosOffsets[index]; }
	void write(ofstream &f);
	~LFLF();
};

#endif

