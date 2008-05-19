#include "DCOS.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Costume.hpp"
#include "blocks/resource/LECF.hpp"
#include "blocks/resource/LFLF.hpp"

DCOS::DCOS(Game *game, LECF *lecf)
{
	_nItems = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfCostumes(); j++)
			if (game->getRoom(i)->getCostume(j)->getID() + 1 > _nItems)
				_nItems = game->getRoom(i)->getCostume(j)->getID() + 1;
	for (int i = 0; i < _nItems; i++)
	{
		_ids.push_back(0);
		_offsets.push_back(0);
	}
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfCostumes(); j++)
		{
			_ids[game->getRoom(i)->getCostume(j)->getID()] = game->getRoom(i)->getCostume(j)->getID();
			_offsets[game->getRoom(i)->getCostume(j)->getID()] = 0;//lecf->getLFLF(i)->getCOSTOffset(j);
		}
}

uint32_t DCOS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // nItems
	size += _nItems * sizeof(uint8_t); // ids
	size += _nItems * sizeof(uint32_t); // offsets
	return size;
}

void DCOS::write(ofstream &f)
{
	IO::writeString(f, "DCOS");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DCOS::~DCOS()
{
}

