#include "EXCD.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

EXCD::EXCD(Script *script)
{
  _bytes.push_back(0x00);
}

uint32_t EXCD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void EXCD::write(ofstream &f)
{
	IO::writeString(f, "EXCD");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

EXCD::~EXCD()
{
}

