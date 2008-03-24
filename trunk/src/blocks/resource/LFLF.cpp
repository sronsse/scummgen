#include "LFLF.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"
#include "ROOM.hpp"
#include "RMSC.hpp"
#include "SCRP.hpp"
#include "SOUN.hpp"
#include "AKOS.hpp"

LFLF::LFLF(Room *room)
{
	_room = new ROOM(room);
	_rmsc = new RMSC(room);
	for (int i = 0; i < room->getNumberOfGlobalScripts(); i++)
		_scrps.push_back(new SCRP(room->getGlobalScript(i)));
	/*for (int i = 0; i < room->getNumberOfSounds(); i++)
		_souns.push_back(new SOUN(room->getSound(i)));*/
	for (int i = 0; i < room->getNumberOfCostumes(); i++)
		_akoss.push_back(new AKOS(room->getCostume(i)));
}

uint32_t LFLF::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _room->getSize(); // room
	size += _rmsc->getSize(); // rmsc
	for (int i = 0; i < _scrps.size(); i++)
		size += _scrps[i]->getSize();
	/*for (int i = 0; i < _souns.size(); i++)
		size += _souns[i]->getSize();*/
	for (int i = 0; i < _akoss.size(); i++)
		size += _akoss[i]->getSize();
	return size;
}

void LFLF::write(ofstream &f)
{
	uint32_t roomOffset = (uint32_t)f.tellp();
	IO::writeString(f, "LFLF");
	IO::writeU32BE(f, getSize());
	_room->write(f);
	_rmscOffset = (uint32_t)f.tellp() - roomOffset;
	_rmsc->write(f);
	for (int i = 0; i < _scrps.size(); i++)
	{
		_scrpOffsets.push_back((uint32_t)f.tellp() - roomOffset);
		_scrps[i]->write(f);
	}
	for (int i = 0; i < _akoss.size(); i++)
	{
		_akosOffsets.push_back((uint32_t)f.tellp() - roomOffset);
		_akoss[i]->write(f);
	}
}

LFLF::~LFLF()
{
	delete _room;
	delete _rmsc;
	for (int i = 0; i < _scrps.size(); i++)
		delete _scrps[i];
	for (int i = 0; i < _souns.size(); i++)
		delete _souns[i];
	for (int i = 0; i < _akoss.size(); i++)
		delete _akoss[i];
}

