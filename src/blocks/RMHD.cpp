#include "RMHD.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "types/Room.hpp"
#include "types/Image.hpp"

RMHD::RMHD(Game *game, uint8_t roomIndex)
{
	Room *room = game->getRoom(roomIndex);

	BMPFile bmpFile;
	bmpFile.open(room->getBackground()->getBitmapPath());
	_width = bmpFile.getWidth();
	_height = bmpFile.getHeight();
	_nObjects = room->getNumberOfObjects();

	// In case we're in the first room, we have to consider the global objects also
	if (room->getID() == 1)
		_nObjects += game->getNumberOfObjects();
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

void RMHD::write(fstream &f)
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
