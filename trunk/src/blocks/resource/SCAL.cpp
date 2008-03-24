#include "SCAL.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

const uint8_t SCAL::N_ENTRIES = 4;

SCAL::SCAL(ifstream &f)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	for (int i = 0; i < N_ENTRIES; i++)
	{
		Log::getInstance().write("slot %d\n", i);

		Log::getInstance().indent();

		uint32_t s1 = IO::readU32LE(f);
		_s1s.push_back(s1);
		Log::getInstance().write("s1: %d\n", s1);

		uint32_t y1 = IO::readU32LE(f);
		_y1s.push_back(y1);
		Log::getInstance().write("y1: %d\n", y1);

		uint32_t s2 = IO::readU32LE(f);
		_s2s.push_back(s2);
		Log::getInstance().write("s2: %d\n", s2);

		uint32_t y2 = IO::readU32LE(f);
		_y2s.push_back(y2);
		Log::getInstance().write("y2: %d\n", y2);

		Log::getInstance().unIndent();
	}

	Log::getInstance().unIndent();
}

uint32_t SCAL::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += N_ENTRIES * sizeof(uint32_t); // s1s
	size += N_ENTRIES * sizeof(uint32_t); // y1s
	size += N_ENTRIES * sizeof(uint32_t); // s2s
	size += N_ENTRIES * sizeof(uint32_t); // y2s
	return size;
}

void SCAL::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "SCAL");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < N_ENTRIES; i++)
	{
		IO::writeU32LE(f, _s1s[i]);
		IO::writeU32LE(f, _y1s[i]);
		IO::writeU32LE(f, _s2s[i]);
		IO::writeU32LE(f, _y2s[i]);
	}
	Log::getInstance().write("SCAL: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

SCAL::~SCAL()
{
}

