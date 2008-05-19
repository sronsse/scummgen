#include "TRNS.hpp"
#include "util/IO.hpp"
#include "types/Palette.hpp"

TRNS::TRNS(Palette *palette)
{
	_transparentIndex = palette->getTransparentIndex();
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

void TRNS::write(ofstream &f)
{
	// Identifier
	IO::writeString(f, "TRNS");

	// Block size
	IO::writeU32BE(f, getSize());

	// Transparent index
	IO::writeU8(f, _transparentIndex);

	// End the block with a 0
	IO::writeU8(f, 0);
}

TRNS::~TRNS()
{
}

