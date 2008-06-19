#include "ENCD.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

ENCD::ENCD(Script *script)
{
	script->asm_printDebug();
	script->asm_print_textstring(script->getName());
	for (int i = 0; i < script->getNumberOfBytes(); i++)
		_bytes.push_back(script->getByte(i));

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x00);
	_bytes.push_back(0x00);

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x90);
	_bytes.push_back(0x00);

	_bytes.push_back(0x9C); // roomOps
	_bytes.push_back(0xAE);
/*
	_bytes.push_back(0x00); // pushByte
	_bytes.push_back(0x01);

	_bytes.push_back(0x74); // startSound
*/
	_bytes.push_back(0x00); // pushByte
	_bytes.push_back(200);

	_bytes.push_back(0x00); // pushByte
	_bytes.push_back(0);

	_bytes.push_back(0x5F); // startScriptQuick

	_bytes.push_back(0x00); // pushByte
	_bytes.push_back(10);

	_bytes.push_back(0xB1); // delaySeconds

	_bytes.push_back(0x00); // pushByte
	_bytes.push_back(0);

	_bytes.push_back(0x7C); // stopScript

	for (int i = 0; i < script->getNumberOfBytes(); i++)
		_bytes.push_back(script->getByte(i));
}

uint32_t ENCD::getSize()
{
	uint32_t size = 0;
	size += sizeof(uint32_t); // identifier
	size += sizeof(uint32_t); // size
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void ENCD::write(fstream &f)
{
	IO::writeString(f, "ENCD");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

ENCD::~ENCD()
{
}

