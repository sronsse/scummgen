#include "BOXM.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

BOXM::BOXM(ifstream &f)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	uint8_t box = 0;
	while ((uint32_t)f.tellg() < basePos + _size)
	{
		uint8_t boxA = IO::readU8(f);
		if (boxA == 0xFF)
		{
			box++;
			continue;
		}

		Log::getInstance().write("box %d\n", box);

		Log::getInstance().indent();

		_boxAs.push_back(boxA);
		Log::getInstance().write("boxA: %d\n", boxA);

		uint8_t boxB = IO::readU8(f);
		_boxBs.push_back(boxB);
		Log::getInstance().write("boxB: %d\n", boxB);

		uint8_t dest = IO::readU8(f);
		_dests.push_back(dest);
		Log::getInstance().write("dest: %d\n", dest);

		Log::getInstance().unIndent();
	}

	Log::getInstance().unIndent();
}

uint32_t BOXM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint8_t); // 0xFF
	return size;
}

void BOXM::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "BOXM");
	IO::writeU32BE(f, getSize());
	IO::writeU8(f, 0xFF);
	Log::getInstance().write("BOXM: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

BOXM::~BOXM()
{
}

