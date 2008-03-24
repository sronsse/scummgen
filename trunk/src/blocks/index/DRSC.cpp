#include "DRSC.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "blocks/resource/LECF.hpp"
#include "blocks/resource/LFLF.hpp"

DRSC::DRSC(Game *game, LECF *lecf)
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
	{
		_ids[game->getRoom(i)->getID()] = game->getRoom(i)->getID();
		_offsets[game->getRoom(i)->getID()] = lecf->getLFLF(i)->getRMSCOffset();
	}
}

uint32_t DRSC::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // nItems
	size += _nItems * sizeof(uint8_t); // ids
	size += _nItems * sizeof(uint32_t); // offsets
	return size;
}

void DRSC::write(ofstream &f)
{
	IO::writeString(f, "DRSC");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DRSC::~DRSC()
{
}

