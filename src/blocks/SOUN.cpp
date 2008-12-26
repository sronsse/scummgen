#include "SOUN.hpp"
#include "util/IO.hpp"
#include "SOU.hpp"

SOUN::SOUN(Midi *midi)
{
	_sou = new SOU(midi);
}

uint32_t SOUN::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _sou->getSize(); // sou
	return size;
}

void SOUN::write(fstream &f)
{
	IO::writeString(f, "SOUN");
	IO::writeU32BE(f, getSize());
	_sou->write(f);
}

SOUN::~SOUN()
{
	delete _sou;
}
