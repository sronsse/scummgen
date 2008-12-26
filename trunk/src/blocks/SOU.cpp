#include "SOU.hpp"
#include "util/IO.hpp"
#include "GMD.hpp"

SOU::SOU(Midi *midi)
{
	_gmd = new GMD(midi);
}

uint32_t SOU::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _gmd->getSize(); // gmd
	return size;
}

void SOU::write(fstream &f)
{
	IO::writeString(f, "SOU ");
	IO::writeU32BE(f, getSize());
	_gmd->write(f);
}

SOU::~SOU()
{
	delete _gmd;
}
