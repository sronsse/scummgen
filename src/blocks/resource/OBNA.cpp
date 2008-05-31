#include "OBNA.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"

OBNA::OBNA(Object *object)
{
	_name = object->getName();
}

uint32_t OBNA::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _name.length() * sizeof(uint8_t); // name
	size += sizeof(uint8_t); // 0
	return size;
}

void OBNA::write(ofstream &f)
{
	IO::writeString(f, "OBNA");
	IO::writeU32BE(f, getSize());
	IO::writeString(f, _name);
	IO::writeU8(f, 0);
}

OBNA::~OBNA()
{
}

