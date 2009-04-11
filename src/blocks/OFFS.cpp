#include "OFFS.hpp"
#include "util/IO.hpp"
#include "APAL.hpp"

OFFS::OFFS(vector<APAL *> apals)
{
	uint32_t firstOffset = 0;
	firstOffset += 4 * sizeof(uint8_t); // OFFS identifier
	firstOffset += sizeof(uint32_t); // OFFS size
	firstOffset += apals.size() * sizeof(uint32_t); // APAL offsets
	_offsets.push_back(firstOffset);
	for (int i = 1; i < apals.size(); i++)
		_offsets.push_back(_offsets[i - 1] + apals[i - 1]->getSize());
}

uint32_t OFFS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offsets.size() * sizeof(uint32_t); // offsets
	return size;
}

void OFFS::write(fstream &f)
{
	IO::writeString(f, "OFFS");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _offsets.size(); i++)
		IO::writeU32LE(f, _offsets[i]);
}

OFFS::~OFFS()
{
}

