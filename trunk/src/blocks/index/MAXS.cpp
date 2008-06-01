#include "MAXS.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Object.hpp"

const uint16_t MAXS::UNKNOWN1 = 0;
const uint16_t MAXS::UNKNOWN2 = 0;

MAXS::MAXS(Game *game)
{
	_nVariables = 800;
	_nBitVariables = 2048;
	_nLocalObjects = 200;
	_nArrays = 50;
	_nVerbs = 50;
	_nFlObjects = 5;
	_nInventories = 80;
	_nRooms = game->getNumberOfRooms() + 1;
	_nScripts = 2;
	_nSounds = 1;
	_nCharsets = 5;
	_nCostumes = 1;
	_nGlobalObjects = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfObjects(); j++)
			if (game->getRoom(i)->getObject(j)->getID() + 1 > _nGlobalObjects)
				_nGlobalObjects = game->getRoom(i)->getObject(j)->getID() + 1;
}

uint32_t MAXS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nVariables
	size += sizeof(uint16_t); // unknown
	size += sizeof(uint16_t); // nBitVariables
	size += sizeof(uint16_t); // nLocalObjects
	size += sizeof(uint16_t); // nArrays
	size += sizeof(uint16_t); // unknown
	size += sizeof(uint16_t); // nVerbs
	size += sizeof(uint16_t); // nFlObjects
	size += sizeof(uint16_t); // nInventories
	size += sizeof(uint16_t); // nRooms
	size += sizeof(uint16_t); // nScripts
	size += sizeof(uint16_t); // nSounds
	size += sizeof(uint16_t); // nCharsets
	size += sizeof(uint16_t); // nCostumes
	size += sizeof(uint16_t); // nGlobalObjects
	return size;
}

void MAXS::write(ofstream &f)
{
	IO::writeString(f, "MAXS");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nVariables);
	IO::writeU16LE(f, UNKNOWN1);
	IO::writeU16LE(f, _nBitVariables);
	IO::writeU16LE(f, _nLocalObjects);
	IO::writeU16LE(f, _nArrays);
	IO::writeU16LE(f, UNKNOWN2);
	IO::writeU16LE(f, _nVerbs);
	IO::writeU16LE(f, _nFlObjects);
	IO::writeU16LE(f, _nInventories);
	IO::writeU16LE(f, _nRooms);
	IO::writeU16LE(f, _nScripts);
	IO::writeU16LE(f, _nSounds);
	IO::writeU16LE(f, _nCharsets);
	IO::writeU16LE(f, _nCostumes);
	IO::writeU16LE(f, _nGlobalObjects);
}

MAXS::~MAXS()
{
}

