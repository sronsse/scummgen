#include "APAL.hpp"
#include "util/IO.hpp"
#include "types/Palette.hpp"

APAL::APAL(Palette *globalPalette, Palette *localPalette)
{
	_colors.resize(Palette::MAX_COLORS);
	for (int i = 0; i < localPalette->getCursor(); i++)
		_colors[i] = localPalette->getColor(i);
	for (int i = Palette::MAX_COLORS - 1; i >= globalPalette->getCursor(); i--)
		_colors[i] = globalPalette->getColor(i);
}

uint32_t APAL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _colors.size() * 3 * sizeof(uint8_t); // colors
	return size;
}

void APAL::write(fstream &f)
{
	IO::writeString(f, "APAL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _colors.size(); i++)
	{
		IO::writeU8(f, _colors[i].r);
		IO::writeU8(f, _colors[i].g);
		IO::writeU8(f, _colors[i].b);
	}
}

APAL::~APAL()
{
}

