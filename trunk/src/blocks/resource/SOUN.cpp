#include "SOUN.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "VOC.hpp"

SOUN::SOUN(Sound *sound)
{
	_voc = new VOC(sound);
}

uint32_t SOUN::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _voc->getSize(); // voc
	return size;
}

void SOUN::write(ofstream &f)
{
	IO::writeString(f, "SOUN");
	IO::writeU32BE(f, getSize());
	_voc->write(f);
}

SOUN::~SOUN()
{
}

