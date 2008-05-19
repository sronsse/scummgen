#include "SCRP.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

SCRP::SCRP(Script *script)
{
	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x01);
	_bytes.push_back(0x00);

	_bytes.push_back(0x7B);

	_bytes.push_back(0x01); // pushWord
	_bytes.push_back(0x05);
	_bytes.push_back(0x05);

	_bytes.push_back(0xB1);

	/*_bytes.push_back(0x01); // push
	_bytes.push_back(0x01);
	_bytes.push_back(0x00);
	_bytes.push_back(0x00);
	_bytes.push_back(0x00);

	_bytes.push_back(0x9D); // loadRoom

	_bytes.push_back(0x01); // push
	_bytes.push_back(0x01);
	_bytes.push_back(0x00);
	_bytes.push_back(0x00);
	_bytes.push_back(0x00);

	_bytes.push_back(0xAF); // startSound

	_bytes.push_back(0x01); // push
	_bytes.push_back(0x0A);
	_bytes.push_back(0x0B);
	_bytes.push_back(0x0C);
	_bytes.push_back(0x0D);

	_bytes.push_back(0x6A); // delay*/
}

uint32_t SCRP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void SCRP::write(ofstream &f)
{
	IO::writeString(f, "SCRP");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

SCRP::~SCRP()
{
}

