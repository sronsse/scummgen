#ifndef _ROOM_BLOCK_HPP_
#define _ROOM_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Room;
class RMHD;
class CYCL;
class TRNS;
class PALS;
class RMIM;
class OBIM;
class OBCD;
class EXCD;
class ENCD;
class NLSC;
class LSCR;
class BOXD;
class BOXM;
class SCAL;

class ROOM
{
private:
	RMHD *_rmhd;
	CYCL *_cycl;
	TRNS *_trns;
	PALS *_pals;
	RMIM *_rmim;
	vector<OBIM *> _obims;
	vector<OBCD *> _obcds;
	EXCD *_excd;
	ENCD *_encd;
	NLSC *_nlsc;
	vector<LSCR *> _lscrs;
	BOXD *_boxd;
	BOXM *_boxm;
	SCAL *_scal;
public:
	ROOM(Room *room);
	uint32_t getSize();
	void write(ofstream &f);
	~ROOM();
};

#endif

