#include "FRMT.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

FRMT::FRMT(ifstream &f)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	f.seekg(basePos + _size, ios::beg);

	Log::getInstance().unIndent();
}

uint32_t FRMT::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	return size;
}

void FRMT::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "FRMT");
	IO::writeU32BE(f, getSize());
	Log::getInstance().write("FRMT: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

FRMT::~FRMT()
{
}

