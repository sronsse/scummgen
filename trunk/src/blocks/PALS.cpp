#include "PALS.hpp"
#include "util/IO.hpp"
#include "WRAP.hpp"

PALS::PALS(Palette *globalPalette, Palette *localPalette)
{
	_wrap = new WRAP(globalPalette, localPalette);
}

uint32_t PALS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _wrap->getSize(); // wrap
	return size;
}

void PALS::write(fstream &f)
{
	IO::writeString(f, "PALS");
	IO::writeU32BE(f, getSize());
	_wrap->write(f);
}

PALS::~PALS()
{
	delete _wrap;
}

