#include "LSCR.hpp"
#include "util/IO.hpp"
#include "grammar/Function.hpp"

LSCR::LSCR(Function *function)
{
	_id = function->getID();
	for (int i = 0; i < function->getNumberOfBytes(); i++)
		_bytes.push_back(function->getByte(i));
}

uint32_t LSCR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint8_t); // id
	size += _bytes.size() * sizeof(uint8_t); // bytes
	return size;
}

void LSCR::write(fstream &f)
{
	IO::writeString(f, "LSCR");
	IO::writeU32BE(f, getSize());
	IO::writeU8(f, _id);
	for (int i = 0; i < _bytes.size(); i++)
		IO::writeU8(f, _bytes[i]);
}

LSCR::~LSCR()
{
}

