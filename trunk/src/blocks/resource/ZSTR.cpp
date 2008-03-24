#include "ZSTR.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "WRAP5.hpp"

ZSTR::ZSTR(ifstream &f, uint32_t width, uint32_t height):
_wrap(NULL)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	while ((uint32_t)f.tellg() < basePos + _size)
	{
		string identifier = IO::readString(f, 4);
		Log::getInstance().write("%s\n", identifier.c_str());
		if (identifier == "WRAP")
			_wrap = new WRAP5(f, width, height);
		else
		{
			f.seekg(basePos + _size, ios::beg);
			Log::getInstance().write("Unknown block type !\n");
			break;
		}
	}

	Log::getInstance().unIndent();
}

uint32_t ZSTR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _wrap->getSize(); // wrap
	return size;
}

void ZSTR::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "ZSTR");
	IO::writeU32BE(f, getSize());
	_wrap->write(f);
	Log::getInstance().write("ZSTR: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

ZSTR::~ZSTR()
{
	if (_wrap != NULL)
		delete _wrap;
}

