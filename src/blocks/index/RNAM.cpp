#include "RNAM.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"

const uint8_t RNAM::N_CHARS = 9;
const uint8_t RNAM::XOR_VALUE = 0xFF;

RNAM::RNAM(Game *game)
{
	for (int i = 0; i < game->getNumberOfRooms(); i++)
	{
		_roomIDs.push_back(game->getRoom(i)->getID());
		string roomName = game->getRoom(i)->getName();
		roomName.resize(N_CHARS, ' ');
		for (int i = 0; i < N_CHARS; i++)
			roomName[i] ^= XOR_VALUE;
		_roomNames.push_back(roomName);
	}
}

uint32_t RNAM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _roomIDs.size() * sizeof(uint8_t); // roomIDs
	size += _roomNames.size() * N_CHARS * sizeof(uint8_t); // roomNames
	size += sizeof(uint8_t); // 0
	return size;
}

void RNAM::write(fstream &f)
{
	IO::writeString(f, "RNAM");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _roomIDs.size(); i++)
	{
		IO::writeU8(f, _roomIDs[i]);
		IO::writeString(f, _roomNames[i]);
	}
	IO::writeU8(f, 0);
}

RNAM::~RNAM()
{
}

