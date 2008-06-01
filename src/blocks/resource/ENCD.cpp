#include "ENCD.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

ENCD::ENCD(Script *script)
{
	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x00);
	_bytes.push_back(0x00);

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x90);
	_bytes.push_back(0x00);

	_bytes.push_back(0x9C);
	_bytes.push_back(0xAE);

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0xEF);
	_bytes.push_back(0x00);

	_bytes.push_back(0xB1);

	_bytes.push_back(0xAE);
	_bytes.push_back(0xA0);
}

uint32_t ENCD::getSize()
{
	uint32_t size = 0;
	size += sizeof(uint32_t); // identifier
	size += sizeof(uint32_t); // size
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void ENCD::write(ofstream &f)
{
	IO::writeString(f, "ENCD");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

ENCD::~ENCD()
{
}

