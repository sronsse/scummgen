#include "LFLF.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"
#include "ROOM.hpp"
#include "SCRP.hpp"
#include "COST.hpp"
#include "CHAR.hpp"

LFLF::LFLF(Room *room)
{
	_room = new ROOM(room);
	for (int i = 0; i < room->getNumberOfGlobalScripts(); i++)
		_scrps.push_back(new SCRP(room->getGlobalScript(i)));
	for (int i = 0; i < room->getNumberOfCostumes(); i++)
		_costs.push_back(new COST(room->getCostume(i)));
	for (int i = 0; i < room->getNumberOfCharsets(); i++)
		_chars.push_back(new CHAR(room->getCharset(i)));
}

uint32_t LFLF::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _room->getSize(); // room
	for (int i = 0; i < _scrps.size(); i++) // scrps
		size += _scrps[i]->getSize();
	for (int i = 0; i < _costs.size(); i++) // costs
		size += _costs[i]->getSize();
	for (int i = 0; i < _chars.size(); i++) // chars
		size += _chars[i]->getSize();
	return size;
}

void LFLF::write(ofstream &f)
{
	IO::writeString(f, "LFLF");
	IO::writeU32BE(f, getSize());
	uint32_t roomOffset = (uint32_t)f.tellp();
	_room->write(f);
	for (int i = 0; i < _scrps.size(); i++)
	{
		_scrpOffsets.push_back((uint32_t)f.tellp() - roomOffset);
		_scrps[i]->write(f);
	}
	for (int i = 0; i < _costs.size(); i++)
	{
		_costOffsets.push_back((uint32_t)f.tellp() - roomOffset);
		_costs[i]->write(f);
	}
	for (int i = 0; i < _chars.size(); i++)
	{
		_charOffsets.push_back((uint32_t)f.tellp() - roomOffset);
		_chars[i]->write(f);
	}
}

LFLF::~LFLF()
{
	delete _room;
	for (int i = 0; i < _scrps.size(); i++)
		delete _scrps[i];
	for (int i = 0; i < _costs.size(); i++)
		delete _costs[i];
	for (int i = 0; i < _chars.size(); i++)
		delete _chars[i];
}

