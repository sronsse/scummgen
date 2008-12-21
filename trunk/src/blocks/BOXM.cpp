#include "BOXM.hpp"
#include "util/IO.hpp"
#include "types/Map.hpp"

const uint8_t BOXM::BOX_END = 0xFF;

BOXM::BOXM(Map *map)
{
	vector<uint8_t> from;
	vector<uint8_t> to;
	vector<uint8_t> dests;

	// Add fake box entries
	from.push_back(0);
	to.push_back(0);
	dests.push_back(0);
	_from.push_back(from);
	_to.push_back(to);
	_dests.push_back(dests);

	for (int i = 0; i < map->getNumberOfBoxes(); i++)
	{
		from.clear();
		to.clear();
		dests.clear();
		for (int j = 0; j < map->getMatrix()->getNumberOfEntries(i); j++)
		{
			from.push_back(map->getMatrix()->getFrom(i, j));
			to.push_back(map->getMatrix()->getTo(i, j));
			dests.push_back(map->getMatrix()->getDest(i, j));
		}
		_from.push_back(from);
		_to.push_back(to);
		_dests.push_back(dests);
	}
}

uint32_t BOXM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	for (int i = 0; i < _from.size(); i++)
	{
		size += _from[i].size() * sizeof(uint8_t); // from
		size += _dests[i].size() * sizeof(uint8_t); // to
		size += _dests[i].size() * sizeof(uint8_t); // dest
	}
	size += _from.size() * sizeof(uint8_t); // BOX_END
	return size;
}

void BOXM::write(fstream &f)
{
	IO::writeString(f, "BOXM");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _from.size(); i++)
	{
		for (int j = 0; j < _from[i].size(); j++)
		{
			IO::writeU8(f, _from[i][j]);
			IO::writeU8(f, _to[i][j]);
			IO::writeU8(f, _dests[i][j]);
		}
		IO::writeU8(f, BOX_END);
	}
}

BOXM::~BOXM()
{
}

