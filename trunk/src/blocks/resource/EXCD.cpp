#include "EXCD.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

EXCD::EXCD(Script *script)
{
	script->asm_printDebug();
	script->asm_print_textstring(script->getName());
	for (int i = 0; i < script->getNumberOfBytes(); i++)
		_bytes.push_back(script->getByte(i));

	for (int i = 0; i < script->getNumberOfBytes(); i++)
		_bytes.push_back(script->getByte(i));
}

uint32_t EXCD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void EXCD::write(fstream &f)
{
	IO::writeString(f, "EXCD");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

EXCD::~EXCD()
{
}

