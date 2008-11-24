#include "BOXD.hpp"
#include "util/IO.hpp"
#include "types/Map.hpp"

const uint32_t BOXD::UNKNOWN = 0;

BOXD::BOXD(Map *map)
{
	_nBoxes = map->getNumberOfBoxes();
	for (int i = 0; i < _nBoxes; i++)
	{
		_ulxs.push_back(map->getBox(i)->getULX());
		_ulys.push_back(map->getBox(i)->getULY());
		_urxs.push_back(map->getBox(i)->getURX());
		_urys.push_back(map->getBox(i)->getURY());
		_lrxs.push_back(map->getBox(i)->getLRX());
		_lrys.push_back(map->getBox(i)->getLRY());
		_llxs.push_back(map->getBox(i)->getLLX());
		_llys.push_back(map->getBox(i)->getLLY());
		_masks.push_back(map->getBox(i)->getMask());
		_flags.push_back(map->getBox(i)->getFlags());
		_scaleSlots.push_back(map->getBox(i)->getScaleSlot());
		_scales.push_back(map->getBox(i)->getScale());
	}
}

uint32_t BOXD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // _nBoxes
	size += _nBoxes * sizeof(uint32_t); // ulxs
	size += _nBoxes * sizeof(uint32_t); // ulys
	size += _nBoxes * sizeof(uint32_t); // urxs
	size += _nBoxes * sizeof(uint32_t); // urys
	size += _nBoxes * sizeof(uint32_t); // lrxs
	size += _nBoxes * sizeof(uint32_t); // lrys
	size += _nBoxes * sizeof(uint32_t); // llxs
	size += _nBoxes * sizeof(uint32_t); // llys
	size += _nBoxes * sizeof(uint32_t); // masks
	size += _nBoxes * sizeof(uint32_t); // flags
	size += _nBoxes * sizeof(uint32_t); // scaleSlots
	size += _nBoxes * sizeof(uint32_t); // scales
	size += _nBoxes * sizeof(uint32_t); // unknown
	return size;
}

void BOXD::write(fstream &f)
{
	IO::writeString(f, "BOXD");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, _nBoxes);
	for (int i = 0; i < _nBoxes; i++)
	{
		IO::writeU32LE(f, _ulxs[i]);
		IO::writeU32LE(f, _ulys[i]);
		IO::writeU32LE(f, _urxs[i]);
		IO::writeU32LE(f, _urys[i]);
		IO::writeU32LE(f, _lrxs[i]);
		IO::writeU32LE(f, _lrys[i]);
		IO::writeU32LE(f, _llxs[i]);
		IO::writeU32LE(f, _llys[i]);
		IO::writeU32LE(f, _masks[i]);
		IO::writeU32LE(f, _flags[i]);
		IO::writeU32LE(f, _scaleSlots[i]);
		IO::writeU32LE(f, _scales[i]);
		IO::writeU32LE(f, UNKNOWN);
	}
}

BOXD::~BOXD()
{
}

