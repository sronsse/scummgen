#include "MAP.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "FRMT.hpp"

MAP::MAP(ifstream &f)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	while ((uint32_t)f.tellg() < basePos + _size)
	{
		string identifier = IO::readString(f, 4);
		Log::getInstance().write("%s\n", identifier.c_str());
		if (identifier == "FRMT")
			_frmt = new FRMT(f);
		/*else if (identifier == "CYCL")
			_cycl = new CYCL(f);
		else if (identifier == "PALS")
			_pals = new PALS(f);*/
		else
		{
			f.seekg(basePos + _size, ios::beg);
			Log::getInstance().write("Unknown block type !\n");
			break;
		}
	}

	Log::getInstance().unIndent();
}

uint32_t MAP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	return size;
}

void MAP::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "MAP");
	IO::writeU32BE(f, getSize());
	Log::getInstance().write("MAP: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

MAP::~MAP()
{
	delete _frmt;
}

