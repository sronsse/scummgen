#include "SCRP.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

SCRP::SCRP(Script *script)
{
	script->asm_printDebug();
	script->asm_print_textstring(script->getName());
	script->asm_pushWord(0x0105);
	script->asm_roomOps();
	script->asm_roomOps_roomFade();
	for (int i = 0; i < script->getNumberOfBytes(); i++)
		_bytes.push_back(script->getByte(i));

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x01);
	_bytes.push_back(0x00);

	_bytes.push_back(0x7B);

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x05);
	_bytes.push_back(0x05);

	_bytes.push_back(0xB1);
}

uint32_t SCRP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void SCRP::write(fstream &f)
{
	IO::writeString(f, "SCRP");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

SCRP::~SCRP()
{
}

