#include "AKHD.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

const uint16_t AKHD::UNKNOWN1 = 1;
const uint8_t AKHD::N_DIRECTIONS_DIVIDER = 4;
const uint8_t AKHD::UNKNOWN2 = 128;
const uint16_t AKHD::UNKNOWN3 = 16;

AKHD::AKHD(Costume *costume)
{
	_flags = costume->isMirror() | ((costume->getNumberOfDirections() / N_DIRECTIONS_DIVIDER) << 1);
	_nAnims = costume->getNumberOfAnims();
	_nFrames = costume->getNumberOfFrames();
	_codec = costume->getCodec();
}

uint32_t AKHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // unknown
	size += sizeof(uint8_t); // flags
	size += sizeof(uint8_t); // unknown
	size += sizeof(uint16_t); // nAnims
	size += sizeof(uint16_t); // nFrames
	size += sizeof(uint16_t); // codec
	size += sizeof(uint16_t); // unknown
	return size;
}

void AKHD::write(ofstream &f)
{
	IO::writeString(f, "AKHD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, UNKNOWN1);
	IO::writeU8(f, _flags);
	IO::writeU8(f, UNKNOWN2);
	IO::writeU16LE(f, _nAnims);
	IO::writeU16LE(f, _nFrames);
	IO::writeU16LE(f, _codec);
	IO::writeU16LE(f, UNKNOWN3);
}

AKHD::~AKHD()
{
}

