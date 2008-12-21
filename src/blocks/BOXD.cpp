#include "BOXD.hpp"
#include "util/IO.hpp"
#include "types/Map.hpp"

const uint16_t BOXD::FAKE_VALUE = 0x8300;
const uint8_t BOXD::FAKE_MASK = 0;
const uint8_t BOXD::FAKE_FLAGS = 0;
const uint8_t BOXD::FAKE_SCALE = 255;

BOXD::BOXD(Map *map)
{
	// Add fake box
	_ulxs.push_back(FAKE_VALUE);
	_ulys.push_back(FAKE_VALUE);
	_urxs.push_back(FAKE_VALUE);
	_urys.push_back(FAKE_VALUE);
	_lrxs.push_back(FAKE_VALUE);
	_lrys.push_back(FAKE_VALUE);
	_llxs.push_back(FAKE_VALUE);
	_llys.push_back(FAKE_VALUE);
	_masks.push_back(FAKE_MASK);
	_flags.push_back(FAKE_MASK);
	_scales.push_back(FAKE_SCALE);

	for (int i = 0; i < map->getNumberOfBoxes(); i++)
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
		_scales.push_back(map->getBox(i)->getScale());
	}

	_nBoxes = map->getNumberOfBoxes() + 1;
}

uint32_t BOXD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // _nBoxes
	size += _nBoxes * sizeof(int16_t); // ulxs
	size += _nBoxes * sizeof(int16_t); // ulys
	size += _nBoxes * sizeof(int16_t); // urxs
	size += _nBoxes * sizeof(int16_t); // urys
	size += _nBoxes * sizeof(int16_t); // lrxs
	size += _nBoxes * sizeof(int16_t); // lrys
	size += _nBoxes * sizeof(int16_t); // llxs
	size += _nBoxes * sizeof(int16_t); // llys
	size += _nBoxes * sizeof(uint8_t); // masks
	size += _nBoxes * sizeof(uint8_t); // flags
	size += _nBoxes * sizeof(uint16_t); // scales
	return size;
}

void BOXD::write(fstream &f)
{
	IO::writeString(f, "BOXD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nBoxes); // Only the lower 8 bits
	for (int i = 0; i < _nBoxes; i++)
	{
		IO::writeU16LE(f, _ulxs[i]);
		IO::writeU16LE(f, _ulys[i]);
		IO::writeU16LE(f, _urxs[i]);
		IO::writeU16LE(f, _urys[i]);
		IO::writeU16LE(f, _lrxs[i]);
		IO::writeU16LE(f, _lrys[i]);
		IO::writeU16LE(f, _llxs[i]);
		IO::writeU16LE(f, _llys[i]);
		IO::writeU8(f, _masks[i]);
		IO::writeU8(f, _flags[i]);
		IO::writeU16LE(f, _scales[i]);
	}
}

BOXD::~BOXD()
{
}

