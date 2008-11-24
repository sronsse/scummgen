#include "CDHD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"

const uint16_t CDHD::UNKNOWN_1 = 0;
const uint16_t CDHD::UNKNOWN_2 = 0;

CDHD::CDHD(Object *object)
{
	_id = object->getID();
	_x = object->getX();
	_y = object->getY();
	_width = object->getWidth();
	_height = object->getHeight();
	_flags = object->getFlags();
	_parent = object->getParent();
	_actorDir = object->getActorDir();
}

uint32_t CDHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // id
	size += sizeof(uint16_t); // x
	size += sizeof(uint16_t); // y
	size += sizeof(uint16_t); // width
	size += sizeof(uint16_t); // height
	size += sizeof(uint8_t); // flags
	size += sizeof(uint8_t); // parent
	size += sizeof(uint16_t); // unknown
	size += sizeof(uint16_t); // unknown
	size += sizeof(uint8_t); // actorDir
	return size;
}

void CDHD::write(fstream &f)
{
	IO::writeString(f, "CDHD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _id);
	IO::writeU16LE(f, _x);
	IO::writeU16LE(f, _y);
	IO::writeU16LE(f, _width);
	IO::writeU16LE(f, _height);
	IO::writeU8(f, _flags);
	IO::writeU8(f, _parent);
	IO::writeU16LE(f, UNKNOWN_1);
	IO::writeU16LE(f, UNKNOWN_2);
	IO::writeU8(f, _actorDir);
}

CDHD::~CDHD()
{
}

