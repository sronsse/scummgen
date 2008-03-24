#include "DROO.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"

DROO::DROO(Game *game)
{
	_nItems = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		if (game->getRoom(i)->getID() + 1 > _nItems)
			_nItems = game->getRoom(i)->getID() + 1;
	for (int i = 0; i < _nItems; i++)
	{
		_ids.push_back(0);
		_offsets.push_back(0);
	}
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		_ids[game->getRoom(i)->getID()] = 1;
}

uint32_t DROO::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // nItems
	size += _nItems * sizeof(uint8_t); // ids
	size += _nItems * sizeof(uint32_t); // offsets
	return size;
}

void DROO::write(ofstream &f)
{
	IO::writeString(f, "DROO");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DROO::~DROO()
{
}

