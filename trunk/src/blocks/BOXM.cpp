#include "BOXM.hpp"
#include "util/IO.hpp"
#include "types/Map.hpp"

const uint8_t BOXM::BOX_END = 0xFF;

BOXM::BOXM(Map *map)
{
	for (int i = 0; i < map->getNumberOfBoxes(); i++)
	{
		vector<uint8_t> boxAs;
		vector<uint8_t> boxBs;
		vector<uint8_t> dests;
		for (int j = 0; j < map->getNumberOfBoxes(); j++)
		{
			boxAs.push_back(i);
			boxBs.push_back(j);
			dests.push_back(map->getMatrix()->getDest(i, j));
		}
		_boxAs.push_back(boxAs);
		_boxBs.push_back(boxBs);
		_dests.push_back(dests);
	}
}

uint32_t BOXM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	for (int i = 0; i < _boxAs.size(); i++)
	{
		size += _boxAs[i].size() * sizeof(uint8_t);
		size += _boxBs[i].size() * sizeof(uint8_t);
		size += _dests[i].size() * sizeof(uint8_t);
	}
	size += _boxAs.size() * sizeof(uint8_t); // BOX_END
	return size;
}

void BOXM::write(fstream &f)
{
	IO::writeString(f, "BOXM");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _boxAs.size(); i++)
	{
		for (int j = 0; j < _boxAs[i].size(); j++)
		{
			IO::writeU8(f, _boxAs[i][j]);
			IO::writeU8(f, _boxBs[i][j]);
			IO::writeU8(f, _dests[i][j]);
		}
		IO::writeU8(f, BOX_END);
	}
}

BOXM::~BOXM()
{
}

