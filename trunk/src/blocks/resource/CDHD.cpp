#include "CDHD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"

const uint32_t CDHD::VERSION = 801;

CDHD::CDHD(Object *object)
{
	_id = object->getID();
	_parent = object->getParent();
	_parentState = object->getParentState();
}

uint32_t CDHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // version
	size += sizeof(uint16_t); // id
	size += sizeof(uint8_t); // parent
	size += sizeof(uint8_t); // parentState
	return size;
}

void CDHD::write(ofstream &f)
{
	IO::writeString(f, "CDHD");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, VERSION);
	IO::writeU16LE(f, _id);
	IO::writeU8(f, _parent);
	IO::writeU8(f, _parentState);
}

CDHD::~CDHD()
{
}

