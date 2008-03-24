#include "AKPL.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

const uint8_t AKPL::N_CHANNELS = 3;

AKPL::AKPL(Costume *costume)
{
	for (int i = 0; i < costume->getNumberOfColors(); i++)
		for (int j = 0; j < N_CHANNELS; j++)
		_palette.push_back(costume->getColor(i, j));
}

uint32_t AKPL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _palette.size() * sizeof(uint8_t); // palette
	return size;
}

void AKPL::write(ofstream &f)
{
	IO::writeString(f, "AKPL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _palette.size(); i++)
		IO::writeU8(f, _palette[i]);
}

AKPL::~AKPL()
{
}

