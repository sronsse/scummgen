#include "OFFS.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "APAL.hpp"
#include "SMAP.hpp"
#include "BOMP.hpp"

OFFS::OFFS(vector<APAL *> apals)
{
	uint32_t firstOffset = 0;
	firstOffset += 4 * sizeof(uint8_t); // identifier
	firstOffset += sizeof(uint32_t); // size
	firstOffset += apals.size() * sizeof(uint32_t); // offsets
	_offsets.push_back(firstOffset);
	for (int i = 1; i < apals.size(); i++)
		_offsets.push_back(_offsets[i - 1] + apals[i - 1]->getSize());
}

OFFS::OFFS(vector<SMAP *> smaps, vector<BOMP *> bomps)
{
	uint32_t firstOffset = 0;
	firstOffset += 4 * sizeof(uint8_t); // identifier
	firstOffset += sizeof(uint32_t); // size
	firstOffset += smaps.size() * sizeof(uint32_t) + bomps.size() * sizeof(uint32_t); // offsets
	_offsets.push_back(firstOffset);
	for (int i = 1; i < smaps.size(); i++)
		_offsets.push_back(_offsets[i - 1] + smaps[i - 1]->getSize());
	for (int i = 1; i < bomps.size(); i++)
		_offsets.push_back(_offsets[i - 1] + bomps[i - 1]->getSize());
}

OFFS::OFFS(vector<vector<uint8_t> > strips)
{
	uint32_t firstOffset = 0;
	firstOffset += 4 * sizeof(uint8_t); // identifier
	firstOffset += sizeof(uint32_t); // size
	firstOffset += strips.size() * sizeof(uint32_t); // offsets
	_offsets.push_back(firstOffset);
	for (int i = 1; i < strips.size(); i++)
		_offsets.push_back(_offsets[i - 1] + strips[i - 1].size());
}

uint32_t OFFS::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offsets.size() * sizeof(uint32_t); // offsets
	return size;
}

void OFFS::write(ofstream &f)
{
	IO::writeString(f, "OFFS");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _offsets.size(); i++)
		IO::writeU32LE(f, _offsets[i]);
}

OFFS::~OFFS()
{
}

