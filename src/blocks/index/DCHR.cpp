#include "DCHR.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Charset.hpp"
#include "blocks/resource/LECF.hpp"
#include "blocks/resource/LFLF.hpp"

DCHR::DCHR(Game *game, LECF *lecf)
{
	_nItems = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfCharsets(); j++)
			if (game->getRoom(i)->getCharset(j)->getID() + 1 > _nItems)
				_nItems = game->getRoom(i)->getCharset(j)->getID() + 1;
	for (int i = 0; i < _nItems; i++)
	{
		_ids.push_back(0);
		_offsets.push_back(0);
	}
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfCharsets(); j++)
		{
			_ids[game->getRoom(i)->getCharset(j)->getID()] = game->getRoom(i)->getCharset(j)->getID();
			_offsets[game->getRoom(i)->getCharset(j)->getID()] = lecf->getLFLF(i)->getCHAROffset(j);
		}
}

uint32_t DCHR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nItems
	size += _nItems * sizeof(uint8_t); // ids
	size += _nItems * sizeof(uint32_t); // offsets
	return size;
}

void DCHR::write(ofstream &f)
{
	IO::writeString(f, "DCHR");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DCHR::~DCHR()
{
}

