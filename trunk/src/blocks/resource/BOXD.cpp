#include "BOXD.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

const uint32_t BOXD::UNKNOWN = 0;

BOXD::BOXD(ifstream &f)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	_nBoxes = IO::readU32LE(f);
	Log::getInstance().write("nBoxes: %d\n", _nBoxes);

	for (int i = 0; i < _nBoxes; i++)
	{
		Log::getInstance().write("box %d\n", i);

		Log::getInstance().indent();

		uint32_t ulx = IO::readU32LE(f);
		_ulxs.push_back(ulx);
		uint32_t uly = IO::readU32LE(f);
		_ulys.push_back(uly);
		Log::getInstance().write("ul: (%d, %d)\n", ulx, uly);

		uint32_t urx = IO::readU32LE(f);
		_urxs.push_back(urx);
		uint32_t ury = IO::readU32LE(f);
		_urys.push_back(ury);
		Log::getInstance().write("ur: (%d, %d)\n", urx, ury);

		uint32_t lrx = IO::readU32LE(f);
		_lrxs.push_back(lrx);
		uint32_t lry = IO::readU32LE(f);
		_lrys.push_back(lry);
		Log::getInstance().write("lr: (%d, %d)\n", lrx, lry);

		uint32_t llx = IO::readU32LE(f);
		_llxs.push_back(llx);
		uint32_t lly = IO::readU32LE(f);
		_llys.push_back(lly);
		Log::getInstance().write("ll: (%d, %d)\n", llx, lly);

		uint32_t mask = IO::readU32LE(f);
		_masks.push_back(mask);
		Log::getInstance().write("mask: %d\n", mask);

		uint32_t flags = IO::readU32LE(f);
		_flags.push_back(flags);
		Log::getInstance().write("flags: %d\n", flags);

		uint32_t scaleSlot = IO::readU32LE(f);
		_scaleSlots.push_back(scaleSlot);
		Log::getInstance().write("scaleSlot: %d\n", scaleSlot);

		uint32_t scale = IO::readU32LE(f);
		_scales.push_back(scale);
		Log::getInstance().write("scales: %d\n", scale);

		uint32_t dummy = IO::readU32LE(f);
		Log::getInstance().write("?: %d\n", dummy);

		Log::getInstance().unIndent();
	}

	Log::getInstance().unIndent();
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

void BOXD::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
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
	Log::getInstance().write("BOXD: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

BOXD::~BOXD()
{
}

