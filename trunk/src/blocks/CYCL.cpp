#include "CYCL.hpp"
#include "util/IO.hpp"
#include "types/Palette.hpp"

const uint16_t CYCL::FREQUENCY = 0x4000;
const uint16_t CYCL::FORWARD = 0x0000;
const uint16_t CYCL::BACKWARD = 0x0002;
const uint16_t CYCL::UNKNOWN = 0;

CYCL::CYCL(Palette *palette)
{
	for (int i = 0; i < palette->getNumberOfCycles(); i++)
	{
		_ids.push_back(palette->getCycle(i)->getID());
		_freqs.push_back(palette->getCycle(i)->getDelay() != 0 ? FREQUENCY / palette->getCycle(i)->getDelay() : 0);
		_flags.push_back(palette->getCycle(i)->isForward() ? FORWARD : BACKWARD);
		_starts.push_back(palette->getCycle(i)->getStart());
		_ends.push_back(palette->getCycle(i)->getEnd());
	}
}

uint32_t CYCL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _ids.size() * sizeof(uint8_t); // ids
	size += _ids.size() * sizeof(uint16_t); // unknown
	size += _freqs.size() * sizeof(uint16_t); // freqs
	size += _flags.size() * sizeof(uint16_t); // flags
	size += _starts.size() * sizeof(uint8_t); // starts
	size += _ends.size() * sizeof(uint8_t); // ends
	size += sizeof(uint8_t); // 0
	return size;
}

void CYCL::write(fstream &f)
{
	IO::writeString(f, "CYCL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _ids.size(); i++)
	{
		IO::writeU8(f, _ids[i]);
		IO::writeU16LE(f, UNKNOWN);
		IO::writeU16BE(f, _freqs[i]);
		IO::writeU16BE(f, _flags[i]);
		IO::writeU8(f, _starts[i]);
		IO::writeU8(f, _ends[i]);
	}
	IO::writeU8(f, 0);
}

CYCL::~CYCL()
{
}

