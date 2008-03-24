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
class PALS;
class IMAG;
class OBIM;
class BOXD;
class BOXM;
class SCAL;

class ROOM
{
private:
	RMHD *_rmhd;
	CYCL *_cycl;
	PALS *_pals;
	IMAG *_imag;
	vector<OBIM *> _obims;
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

