#ifndef _RMSC_BLOCK_HPP_
#define _RMSC_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Room;
class ENCD;
class EXCD;
class LSCR;
class OBCD;

class RMSC
{
private:
	uint32_t _size;
	ENCD *_encd;
	EXCD *_excd;
	vector<LSCR *> _lscrs;
	vector<OBCD *> _obcds;
public:
	RMSC(Room *room);
	uint32_t getSize();
	void write(ofstream &f);
	~RMSC();
};

#endif

