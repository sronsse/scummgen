#include "MAXS.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Object.hpp"

const uint8_t MAXS::N_CHARS = 50;
const uint8_t MAXS::UNKNOWN1 = 40;
const uint8_t MAXS::UNKNOWN2 = 80;
const uint8_t MAXS::UNKNOWN3 = 60;

MAXS::MAXS(Game *game)
{
	_engineVersion = "SCUMM.EXE version 8.1.0 (Aug 28 1997 17:50:54)";
	_engineVersion.resize(N_CHARS, ' ');
	_dataFileVersion = "Scripts compiled Wed Oct 15 1997 18:21:17";
	_dataFileVersion.resize(N_CHARS, ' ');
	_nVariables = 1500;
	_nBitVariables = 2048;
	_nScripts = 2;
	_nSounds = 789;
	_nCharsets = 1;
	_nCostumes = 446;
	_nRooms = game->getNumberOfRooms() + 1;
	_nGlobalObjects = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfObjects(); j++)
			if (game->getRoom(i)->getObject(j)->getID() + 1 > _nGlobalObjects)
				_nGlobalObjects = game->getRoom(i)->getObject(j)->getID() + 1;
	_nLocalObjects = 2;
	_nNewNames = 100;
	_nFlObjects = 128;
	_nInventories = 80;
	_nArrays = 200;
	_nVerbs = 50;
}

uint32_t MAXS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += N_CHARS * sizeof(uint8_t); // engineVersion
	size += N_CHARS * sizeof(uint8_t); // dataFileVersion
	size += sizeof(uint32_t); // nVariables
	size += sizeof(uint32_t); // nBitVariables
	size += sizeof(uint32_t); // unknown
	size += sizeof(uint32_t); // nScripts
	size += sizeof(uint32_t); // nSounds
	size += sizeof(uint32_t); // nCharsets
	size += sizeof(uint32_t); // nCostumes
	size += sizeof(uint32_t); // nRooms
	size += sizeof(uint32_t); // unknown
	size += sizeof(uint32_t); // nGlobalObjects);
	size += sizeof(uint32_t); // unknown
	size += sizeof(uint32_t); // nLocalObjects);
	size += sizeof(uint32_t); // nNewNames);
	size += sizeof(uint32_t); // nFlObjects);
	size += sizeof(uint32_t); // nInventories);
	size += sizeof(uint32_t); // nArrays
	size += sizeof(uint32_t); // nVerbs
	return size;
}

void MAXS::write(ofstream &f)
{
	IO::writeString(f, "MAXS");
	IO::writeU32BE(f, getSize());
	IO::writeString(f, _engineVersion);
	IO::writeString(f, _dataFileVersion);
	IO::writeU32LE(f, _nVariables);
	IO::writeU32LE(f, _nBitVariables);
	IO::writeU32LE(f, UNKNOWN1);
	IO::writeU32LE(f, _nScripts);
	IO::writeU32LE(f, _nSounds);
	IO::writeU32LE(f, _nCharsets);
	IO::writeU32LE(f, _nCostumes);
	IO::writeU32LE(f, _nRooms);
	IO::writeU32LE(f, UNKNOWN2);
	IO::writeU32LE(f, _nGlobalObjects);
	IO::writeU32LE(f, UNKNOWN3);
	IO::writeU32LE(f, _nLocalObjects);
	IO::writeU32LE(f, _nNewNames);
	IO::writeU32LE(f, _nFlObjects);
	IO::writeU32LE(f, _nInventories);
	IO::writeU32LE(f, _nArrays);
	IO::writeU32LE(f, _nVerbs);
}

MAXS::~MAXS()
{
}

