#include "LSCR.hpp"
#include "util/IO.hpp"
#include "types/Script.hpp"

LSCR::LSCR(Script *script)
{
	_index = script->getID();
	for (int i = 0; i < script->getNumberOfBytes(); i++)
		_bytes.push_back(script->getByte(i));
}

uint32_t LSCR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint8_t); // index
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void LSCR::write(ofstream &f)
{
	IO::writeString(f, "LSCR");
	IO::writeU32BE(f, getSize());
	IO::writeU8(f, _index);
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

LSCR::~LSCR()
{
}

