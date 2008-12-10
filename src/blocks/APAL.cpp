#include "APAL.hpp"
#include "util/IO.hpp"
#include "types/Palette.hpp"

const uint16_t APAL::N_COLORS = 256;

APAL::APAL(Palette *palette)
{
	for (int i = 0; i < palette->getNumberOfColors(); i++)
		_colors.push_back(palette->getColor(i));

	Color black = { 0, 0, 0 };
	for (int i = palette->getNumberOfColors(); i < N_COLORS; i++)
		_colors.push_back(black);
}

uint32_t APAL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += N_COLORS * sizeof(uint8_t); // rs
	size += N_COLORS * sizeof(uint8_t); // gs
	size += N_COLORS * sizeof(uint8_t); // bs
	return size;
}

void APAL::write(fstream &f)
{
	IO::writeString(f, "APAL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < N_COLORS; i++)
	{
		IO::writeU8(f, _colors[i].r);
		IO::writeU8(f, _colors[i].g);
		IO::writeU8(f, _colors[i].b);
	}
}

APAL::~APAL()
{
}

