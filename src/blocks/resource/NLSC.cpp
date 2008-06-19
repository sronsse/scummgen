#include "NLSC.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"

NLSC::NLSC(Room *room)
{
	_nLocalScripts = room->getNumberOfScripts();
}

uint32_t NLSC::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint8_t); // nLocalScripts
	size += sizeof(uint8_t); // 0
	return size;
}

void NLSC::write(fstream &f)
{
	IO::writeString(f, "NLSC");
	IO::writeU32BE(f, getSize());
	IO::writeU8(f, _nLocalScripts);
	IO::writeU8(f, 0);
}

NLSC::~NLSC()
{
}

