#include "ROOM.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"
#include "RMHD.hpp"
#include "CYCL.hpp"
#include "PALS.hpp"
#include "IMAG.hpp"
#include "OBIM.hpp"
#include "BOXD.hpp"
#include "BOXM.hpp"
#include "SCAL.hpp"

ROOM::ROOM(Room *room):
_boxd(NULL),
_boxm(NULL),
_scal(NULL)
{
	_rmhd = new RMHD(room);
	_cycl = new CYCL(room->getPalette());
	_pals = new PALS(room->getPalette());
	_imag = new IMAG(room->getBackground());
	for (int i = 0; i < room->getNumberOfObjects(); i++)
		_obims.push_back(new OBIM(room->getObject(i)));
}

uint32_t ROOM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _rmhd->getSize(); // rmhd
	size += _cycl->getSize(); // cycl
	size += _pals->getSize(); // pals
	size += _imag->getSize(); // imag
	for (int i = 0; i < _obims.size(); i++) // obims
		size += _obims[i]->getSize();
	/*size += _boxd->getSize(); // boxd
	size += _boxm->getSize(); // boxm
	size += _scal->getSize(); // scal*/
	return size;
}

void ROOM::write(ofstream &f)
{
	IO::writeString(f, "ROOM");
	IO::writeU32BE(f, getSize());
	_rmhd->write(f);
	_cycl->write(f);
	_pals->write(f);
	_imag->write(f);
	for (int i = 0; i < _obims.size(); i++)
		_obims[i]->write(f);
	/*_boxd->write(f);
	_boxm->write(f);
	_scal->write(f);*/
}

ROOM::~ROOM()
{
	delete _rmhd;
	delete _cycl;
	delete _pals;
	delete _imag;
	for (int i = 0; i < _obims.size(); i++)
		delete _obims[i];
	if (_boxd != NULL)
		delete _boxd;
	if (_boxm != NULL)
		delete _boxm;
	if (_scal != NULL)
		delete _scal;
}

