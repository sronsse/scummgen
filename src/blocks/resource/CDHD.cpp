#include "CDHD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"

CDHD::CDHD(Object *object)
{
	_id = object->getID();
	_x = object->getX();
	_y = object->getY();
	_width = object->getWidth();
	_height = object->getHeight();
	_flags = object->getFlags();
	_parent = object->getParent();
	_walkX = object->getWalkX();
	_walkY = object->getWalkY();
	_actorDir = object->getActorDir();
}

uint32_t CDHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // id
	size += sizeof(uint8_t); // x
	size += sizeof(uint8_t); // y
	size += sizeof(uint8_t); // width
	size += sizeof(uint8_t); // height
	size += sizeof(uint8_t); // flags
	size += sizeof(uint8_t); // parent
	size += sizeof(uint16_t); // walkX
	size += sizeof(uint16_t); // walkY
	size += sizeof(uint8_t); // actorDir
	return size;
}

void CDHD::write(ofstream &f)
{
	IO::writeString(f, "CDHD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _id);
	IO::writeU8(f, _x);
	IO::writeU8(f, _y);
	IO::writeU8(f, _width);
	IO::writeU8(f, _height);
	IO::writeU8(f, _flags);
	IO::writeU8(f, _parent);
	IO::writeU16LE(f, _walkX);
	IO::writeU16LE(f, _walkY);
	IO::writeU8(f, _actorDir);
}

CDHD::~CDHD()
{
}

