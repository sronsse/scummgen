#include "RMSC.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"
#include "ENCD.hpp"
#include "EXCD.hpp"
#include "LSCR.hpp"
#include "OBCD.hpp"

RMSC::RMSC(Room *room)
{
	_encd = new ENCD(room->getEntryScript());
	_excd = new EXCD(room->getExitScript());
	for (int i = 0; i < room->getNumberOfLocalScripts(); i++)
		_lscrs.push_back(new LSCR(room->getLocalScript(i)));
	for (int i = 0; i < room->getNumberOfObjects(); i++)
		_obcds.push_back(new OBCD(room->getObject(i)));
}

uint32_t RMSC::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _encd->getSize(); // encd
	size += _excd->getSize(); // excd
	for (int i = 0; i < _lscrs.size(); i++) // lscrs
		size += _lscrs[i]->getSize();
	for (int i = 0; i < _obcds.size(); i++) // obcds
		size += _obcds[i]->getSize();
	return size;
}

void RMSC::write(ofstream &f)
{
	IO::writeString(f, "RMSC");
	IO::writeU32BE(f, getSize());
	_encd->write(f);
	_excd->write(f);
	for (int i = 0; i < _lscrs.size(); i++)
		_lscrs[i]->write(f);
	for (int i = 0; i < _obcds.size(); i++)
		_obcds[i]->write(f);
}

RMSC::~RMSC()
{
	delete _encd;
	delete _excd;
	for (int i = 0; i < _lscrs.size(); i++)
		delete _lscrs[i];
	for (int i = 0; i < _obcds.size(); i++)
		delete _obcds[i];
}

