#include "LOFF.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "LFLF.hpp"

LOFF::LOFF(Game *game, vector<LFLF *> lflfs)
{
	_nRooms = game->getNumberOfRooms();
	for (int i = 0; i < _nRooms; i++)
		_roomIDs.push_back(game->getRoom(i)->getID());
	if (_nRooms > 0)
	{
		uint32_t firstOffset = 0;
		firstOffset += 4 * sizeof(uint8_t); // LECF identifier
		firstOffset += sizeof(uint32_t); // LECF size
		firstOffset += getSize(); // LOFF
		/*firstOffset += 4 * sizeof(uint8_t); // LFLF identifier
		firstOffset += sizeof(uint32_t);*/ // LFLF size
		_roomOffsets.push_back(firstOffset);
		for (int i = 1; i < _nRooms; i++)
			_roomOffsets.push_back(_roomOffsets[i - 1] + lflfs[i - 1]->getSize());
	}
}

uint32_t LOFF::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint8_t); // nRooms
	size += _nRooms * sizeof(uint8_t); // roomIDs
	size += _nRooms * sizeof(uint32_t); // roomOffsets
	return size;
}

void LOFF::write(ofstream &f)
{
	IO::writeString(f, "LOFF");
	IO::writeU32BE(f, getSize());
	IO::writeU8(f, _nRooms);
	for (int i = 0; i < _nRooms; i++)
	{
		IO::writeU8(f, _roomIDs[i]);
		IO::writeU32LE(f, _roomOffsets[i]);
	}
}

LOFF::~LOFF()
{
}

