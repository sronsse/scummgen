#include "DOBJ.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Object.hpp"

DOBJ::DOBJ(Game *game)
{
	_ownersAndStates.push_back(0);
	_classData.push_back(0);

	// Actor objects
	for (int i = 0; i < Game::N_DEFAULT_ACTORS; i++)
	{
		_ownersAndStates.push_back(0);
		_classData.push_back(0);
	}

	// Game global objects
	for (int i = 0; i < game->getNumberOfObjects(); i++)
	{
		uint8_t ownerAndState = game->getObject(i)->getFlags() << 4;
		ownerAndState |= game->getObject(i)->getOwner();
		_ownersAndStates.push_back(ownerAndState);
		_classData.push_back(game->getObject(i)->getClassData());
	}

	// Room objects
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfObjects(); j++)
		{
			uint8_t ownerAndState = game->getRoom(i)->getObject(j)->getFlags() << 4;
			ownerAndState |= game->getRoom(i)->getObject(j)->getOwner();
			_ownersAndStates.push_back(ownerAndState);
			_classData.push_back(game->getRoom(i)->getObject(j)->getClassData());
		}

	_nItems = _ownersAndStates.size();
}

uint32_t DOBJ::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nitems
	size += _ownersAndStates.size() * sizeof(uint8_t); // ownersAndStates
	size += _classData.size() * sizeof(uint32_t); // classData
	return size;
}

void DOBJ::write(fstream &f)
{
	IO::writeString(f, "DOBJ");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _ownersAndStates.size(); i++)
		IO::writeU8(f, _ownersAndStates[i]);
	for (int i = 0; i < _classData.size(); i++)
		IO::writeU32LE(f, _classData[i]);
}

DOBJ::~DOBJ()
{
}

