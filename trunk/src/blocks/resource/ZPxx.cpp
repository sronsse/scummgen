#include "ZPxx.hpp"
#include "util/IO.hpp"

ZPxx::ZPxx(ZPlane *zPlane, uint8_t index)
{
	_index = index;
}

uint32_t ZPxx::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	return size;
}

void ZPxx::write(ofstream &f)
{
	IO::writeString(f, "ZP" + IO::getStringFromIndex(_index, 2));
	IO::writeU32BE(f, getSize());
}

ZPxx::~ZPxx()
{
}

