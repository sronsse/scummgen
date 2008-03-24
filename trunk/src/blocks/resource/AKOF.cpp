#include "AKOF.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"
#include "AKCD.hpp"

AKOF::AKOF(Costume *costume, AKCD *akcd)
{
	for (int i = 0; i < costume->getNumberOfFrames(); i++)
	{
		_akcdOffsets.push_back(akcd->getOffset(i));
		_akciOffsets.push_back(i * 2 * sizeof(uint16_t));
	}
}

uint32_t AKOF::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _akcdOffsets.size() * sizeof(uint32_t); // akcdOffsets
	size += _akciOffsets.size() * sizeof(uint16_t); // akciOffsets
	return size;
}

void AKOF::write(ofstream &f)
{
	IO::writeString(f, "AKOF");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _akcdOffsets.size(); i++)
	{
		IO::writeU32LE(f, _akcdOffsets[i]);
		IO::writeU16LE(f, _akciOffsets[i]);
	}
}

AKOF::~AKOF()
{
}

