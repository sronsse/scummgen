#include "ROOM.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "RMHD.hpp"
#include "CYCL.hpp"
#include "TRNS.hpp"
#include "PALS.hpp"
#include "RMIM.hpp"
#include "OBIM.hpp"
#include "OBCD.hpp"
#include "EXCD.hpp"
#include "ENCD.hpp"
#include "NLSC.hpp"
#include "LSCR.hpp"
#include "BOXD.hpp"
#include "BOXM.hpp"
#include "SCAL.hpp"

ROOM::ROOM(Game *game, uint8_t roomIndex)
{
	Room *room = game->getRoom(roomIndex);

	_rmhd = new RMHD(room);
	_cycl = new CYCL(room->getPalette());
	_trns = new TRNS(room->getPalette());
	_pals = new PALS(room->getPalette());
	_rmim = new RMIM(room->getBackground());
	
	// Add global objects to the first room
	if (room->getID() == 1)
	{
		for (int i = 0; i < game->getNumberOfObjects(); i++)
			_obims.push_back(new OBIM(game->getObject(i)));
		for (int i = 0; i < game->getNumberOfObjects(); i++)
			_obcds.push_back(new OBCD(game->getObject(i)));
	}
	
	for (int i = 0; i < room->getNumberOfObjects(); i++)
		_obims.push_back(new OBIM(room->getObject(i)));
	for (int i = 0; i < room->getNumberOfObjects(); i++)
		_obcds.push_back(new OBCD(room->getObject(i)));

	_excd = new EXCD(room->getExitFunction());
	_encd = new ENCD(room->getEntryFunction());
	_nlsc = new NLSC(room);
	for (int i = 0; i < room->getNumberOfFunctions(); i++)
		_lscrs.push_back(new LSCR(room->getFunction(i)));
	_boxd = new BOXD(room->getMap());
	_boxm = new BOXM(room->getMap());
	_scal = new SCAL(room->getMap());
}

uint32_t ROOM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _rmhd->getSize(); // rmhd
	size += _cycl->getSize(); // cycl
	size += _trns->getSize(); // trns
	size += _pals->getSize(); // pals
	size += _rmim->getSize(); // rmim
	for (int i = 0; i < _obims.size(); i++) // obims
		size += _obims[i]->getSize();
	for (int i = 0; i < _obcds.size(); i++) // obcds
		size += _obcds[i]->getSize();
	size += _excd->getSize(); // encd
	size += _encd->getSize(); // excd
	size += _nlsc->getSize(); // nlsc
	for (int i = 0; i < _lscrs.size(); i++) // lscrs
		size += _lscrs[i]->getSize();
	size += _boxd->getSize(); // boxd
	size += _boxm->getSize(); // boxm
	size += _scal->getSize(); // scal
	return size;
}

void ROOM::write(fstream &f)
{
	IO::writeString(f, "ROOM");
	IO::writeU32BE(f, getSize());
	_rmhd->write(f);
	_cycl->write(f);
	_trns->write(f);
	_pals->write(f);
	_rmim->write(f);
	for (int i = 0; i < _obims.size(); i++)
		_obims[i]->write(f);
	for (int i = 0; i < _obcds.size(); i++)
		_obcds[i]->write(f);
	_excd->write(f);
	_encd->write(f);
	_nlsc->write(f);
	for (int i = 0; i < _lscrs.size(); i++)
		_lscrs[i]->write(f);
	_boxd->write(f);
	_boxm->write(f);
	_scal->write(f);
}

ROOM::~ROOM()
{
	delete _rmhd;
	delete _cycl;
	delete _trns;
	delete _pals;
	delete _rmim;
	for (int i = 0; i < _obims.size(); i++)
		delete _obims[i];
	for (int i = 0; i < _obcds.size(); i++)
		delete _obcds[i];
	delete _excd;
	delete _encd;
	delete _nlsc;
	for (int i = 0; i < _lscrs.size(); i++)
		delete _lscrs[i];
	delete _boxd;
	delete _boxm;
	delete _scal;
}

