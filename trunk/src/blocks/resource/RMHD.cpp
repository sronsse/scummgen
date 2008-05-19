#include "RMHD.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"
#include "types/Image.hpp"

RMHD::RMHD(Room *room)
{
	_width = room->getBackground()->getWidth();
	_height = room->getBackground()->getHeight();
	_nObjects = room->getNumberOfObjects();
}

uint32_t RMHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // width
	size += sizeof(uint16_t); // height
	size += sizeof(uint16_t); // nObjects
	return size;
}

void RMHD::write(ofstream &f)
{
	IO::writeString(f, "RMHD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _width);
	IO::writeU16LE(f, _height);
	IO::writeU16LE(f, _nObjects);
}

RMHD::~RMHD()
{
}

