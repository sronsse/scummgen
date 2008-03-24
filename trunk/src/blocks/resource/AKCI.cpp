#include "AKCI.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

AKCI::AKCI(Costume *costume)
{
	for (int i = 0; i < costume->getNumberOfFrames(); i++)
	{
		_widths.push_back(costume->getFrame(i)->getWidth());
		_heights.push_back(costume->getFrame(i)->getHeight());
	}
}

uint32_t AKCI::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _widths.size() * sizeof(uint16_t); // widths
	size += _heights.size() * sizeof(uint16_t); // heights
	return size;
}

void AKCI::write(ofstream &f)
{
	IO::writeString(f, "AKCI");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _widths.size(); i++)
	{
		IO::writeU16LE(f, _widths[i]);
		IO::writeU16LE(f, _heights[i]);
	}
}

AKCI::~AKCI()
{
}

