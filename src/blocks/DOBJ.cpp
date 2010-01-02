#include "DOBJ.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Object.hpp"

const uint8_t DOBJ::OWNER_AND_STATE = 0;
const uint32_t DOBJ::CLASS_DATA = 0;

DOBJ::DOBJ(Game *game)
{
	_ownersAndStates.push_back(OWNER_AND_STATE);
	_classData.push_back(CLASS_DATA);

	// Actor objects
	for (int i = 0; i < Game::N_DEFAULT_ACTORS; i++)
	{
		_ownersAndStates.push_back(OWNER_AND_STATE);
		_classData.push_back(CLASS_DATA);
	}

	// Game global objects
	for (int i = 0; i < game->getNumberOfObjects(); i++)
	{
		_ownersAndStates.push_back(OWNER_AND_STATE);
		_classData.push_back(CLASS_DATA);
	}

	// Room objects
	for (int i = 0; i < game->getNumberOfRooms(); i++)
		for (int j = 0; j < game->getRoom(i)->getNumberOfObjects(); j++)
		{
			_ownersAndStates.push_back(OWNER_AND_STATE);
			_classData.push_back(CLASS_DATA);
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
