#include "TRNS.hpp"
#include "util/IO.hpp"

const uint8_t TRNS::TRANSPARENT_INDEX = 0;

TRNS::TRNS()
{
}

uint32_t TRNS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint8_t); // transparentIndex
	size += sizeof(uint8_t); // 0
	return size;
}

void TRNS::write(fstream &f)
{
	// Identifier
	IO::writeString(f, "TRNS");

	// Block size
	IO::writeU32BE(f, getSize());

	// Transparent index
	IO::writeU8(f, TRANSPARENT_INDEX);

	// End the block with 0
	IO::writeU8(f, 0);
}

TRNS::~TRNS()
{
}

