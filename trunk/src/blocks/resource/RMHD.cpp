#include "RMHD.hpp"
#include "util/IO.hpp"
#include "types/Room.hpp"
#include "types/Image.hpp"
#include "types/Palette.hpp"

const uint16_t RMHD::VERSION = 800;

RMHD::RMHD(Room *room)
{
	_width = room->getBackground()->getWidth();
	_height = room->getBackground()->getHeight();
	_nObjects = room->getNumberOfObjects();
	_nZPlanes = room->getBackground()->getNumberOfZPlanes();
	_transparentIndex = room->getPalette()->getTransparentIndex();
}

uint32_t RMHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // version
	size += sizeof(uint32_t); // width
	size += sizeof(uint32_t); // height
	size += sizeof(uint32_t); // nObjects
	size += sizeof(uint32_t); // nZPlanes
	size += sizeof(uint32_t); // transparentIndex
	return size;
}

void RMHD::write(ofstream &f)
{
	IO::writeString(f, "RMHD");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, VERSION);
	IO::writeU32LE(f, _width);
	IO::writeU32LE(f, _height);
	IO::writeU32LE(f, _nObjects);
	IO::writeU32LE(f, _nZPlanes);
	IO::writeU32LE(f, _transparentIndex);
}

RMHD::~RMHD()
{
}

