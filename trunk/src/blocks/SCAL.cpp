#include "SCAL.hpp"
#include "util/IO.hpp"
#include "types/Map.hpp"

SCAL::SCAL(Map *map)
{
	for (int i = 0; i < map->getNumberOfScales(); i++)
	{
		_s1s.push_back(map->getScale(i)->getS1());
		_y1s.push_back(map->getScale(i)->getY1());
		_s2s.push_back(map->getScale(i)->getS2());
		_y2s.push_back(map->getScale(i)->getY2());
	}
}

uint32_t SCAL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _s1s.size() * sizeof(uint16_t); // s1s
	size += _y1s.size() * sizeof(uint16_t); // y1s
	size += _s2s.size() * sizeof(uint16_t); // s2s
	size += _y2s.size() * sizeof(uint16_t); // y2s
	return size;
}

void SCAL::write(fstream &f)
{
	IO::writeString(f, "SCAL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _s1s.size(); i++)
	{
		IO::writeU16LE(f, _s1s[i]);
		IO::writeU16LE(f, _y1s[i]);
		IO::writeU16LE(f, _s2s[i]);
		IO::writeU16LE(f, _y2s[i]);
	}
}

SCAL::~SCAL()
{
}

