#include "RGBS.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

RGBS::RGBS(Costume *costume)
{
	for (int i = 0; i < costume->getNumberOfColors(); i++)
	{
		_rs.push_back(costume->getColor(i, 2));
		_gs.push_back(costume->getColor(i, 1));
		_bs.push_back(costume->getColor(i, 0));
	}
}

uint32_t RGBS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _rs.size() * sizeof(uint8_t); // rs
	size += _gs.size() * sizeof(uint8_t); // gs
	size += _bs.size() * sizeof(uint8_t); // bs
	return size;
}

void RGBS::write(ofstream &f)
{
	IO::writeString(f, "RGBS");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _rs.size(); i++)
	{
		IO::writeU8(f, _rs[i]);
		IO::writeU8(f, _gs[i]);
		IO::writeU8(f, _bs[i]);
	}
}

RGBS::~RGBS()
{
}

