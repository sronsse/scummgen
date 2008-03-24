#include "WRAP4.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "OFFS.hpp"
#include "ZSTR.hpp"

WRAP4::WRAP4(ifstream &f, uint32_t width, uint32_t height):
_offs(NULL)
{
	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	while ((uint32_t)f.tellg() < basePos + _size)
	{
		string identifier = IO::readString(f, 4);
		Log::getInstance().write("%s\n", identifier.c_str());
		/*if (identifier == "OFFS")
			_offs = new OFFS(f);*/
		if (identifier == "ZSTR")
			_zstrs.push_back(new ZSTR(f, width, height));
		else
		{
			f.seekg(basePos + _size, ios::beg);
			Log::getInstance().write("Unknown block type !\n");
			break;
		}
	}

	Log::getInstance().unIndent();
}

uint32_t WRAP4::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offs->getSize(); // offs
	for (int i = 0; i < _zstrs.size(); i++) // zstrs
		size += _zstrs[i]->getSize();
	return size;
}

void WRAP4::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "WRAP");
	IO::writeU32BE(f, getSize());
	_offs->write(f);
	for (int i = 0; i < _zstrs.size(); i++)
		_zstrs[i]->write(f);
	Log::getInstance().write("WRAP4: %d\n", (uint32_t)f.tellp() - base);
	Log::getInstance().write("Mais le getSize est %d\n", getSize());
}

WRAP4::~WRAP4()
{
	if (_offs != NULL)
		delete _offs;

	for (int i = 0; i < _zstrs.size(); i++)
		delete _zstrs[i];
}

