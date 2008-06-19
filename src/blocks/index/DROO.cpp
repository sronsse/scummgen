#include "DROO.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"

DROO::DROO(Game *game)
{
	_ids.push_back(0);
	_offsets.push_back(0);

	for (int i = 0; i < game->getNumberOfRooms(); i++)
	{
		_ids.push_back(1);
		_offsets.push_back(0);
	}

	_nItems = _ids.size();
}

uint32_t DROO::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nItems
	size += _ids.size() * sizeof(uint8_t); // ids
	size += _offsets.size() * sizeof(uint32_t); // offsets
	return size;
}

void DROO::write(fstream &f)
{
	IO::writeString(f, "DROO");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nItems);
	for (int i = 0; i < _nItems; i++)
		IO::writeU8(f, _ids[i]);
	for (int i = 0; i < _nItems; i++)
		IO::writeU32LE(f, _offsets[i]);
}

DROO::~DROO()
{
}

