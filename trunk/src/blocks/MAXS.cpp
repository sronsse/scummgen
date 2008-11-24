#include "MAXS.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"

const uint8_t MAXS::UNKNOWN1 = 0;
const uint16_t MAXS::N_BIT_VARIABLES = 2048;
const uint8_t MAXS::N_LOCAL_OBJECTS = 200;
const uint8_t MAXS::N_ARRAYS = 50;
const uint8_t MAXS::UNKNOWN2 = 0;
const uint8_t MAXS::N_VERBS = 50;
const uint8_t MAXS::N_FL_OBJECTS = 5;
const uint8_t MAXS::N_INVENTORIES = 80;

MAXS::MAXS(Game *game)
{
	_nVariables = Game::MAX_WORD_VARIABLES;
	_nBitVariables = N_BIT_VARIABLES;
	_nLocalObjects = N_LOCAL_OBJECTS;
	_nArrays = N_ARRAYS;
	_nVerbs = N_VERBS;
	_nFlObjects = N_FL_OBJECTS;
	_nInventories = N_INVENTORIES;
	_nRooms = game->getNumberOfRooms() + 1;
	_nScripts = game->getNumberOfFunctions() + 1;
	_nSounds = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		_nSounds += game->getRoom(i)->getNumberOfSounds();
	_nCharsets = game->getNumberOfCharsets() + 1;
	_nCostumes = 1;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		_nCostumes += game->getRoom(i)->getNumberOfCostumes();
	_nGlobalObjects = Game::N_DEFAULT_ACTORS;
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		_nGlobalObjects += game->getRoom(i)->getNumberOfObjects();
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

void MAXS::write(fstream &f)
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

