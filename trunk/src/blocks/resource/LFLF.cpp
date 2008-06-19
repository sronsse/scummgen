#include "LFLF.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "ROOM.hpp"
#include "SCRP.hpp"
#include "COST.hpp"
#include "CHAR.hpp"

LFLF::LFLF(Game *game, uint8_t roomIndex)
{
	_room = new ROOM(game->getRoom(roomIndex));
	if (game->getRoom(roomIndex)->getID() == 1)
		for (int i = 0; i < game->getNumberOfScripts(); i++)
			_scrps.push_back(new SCRP(game->getScript(i)));
	for (int i = 0; i < game->getRoom(roomIndex)->getNumberOfCostumes(); i++)
		_costs.push_back(new COST(game->getRoom(roomIndex)->getCostume(i)));
	if (game->getRoom(roomIndex)->getID() == 1)
		for (int i = 0; i < game->getNumberOfCharsets(); i++)
			_chars.push_back(new CHAR(game->getCharset(i)));
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

void LFLF::write(fstream &f)
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

