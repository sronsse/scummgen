#include "WRAP.hpp"
#include "util/IO.hpp"
#include "OFFS.hpp"
#include "APAL.hpp"

WRAP::WRAP(Palette *palette)
{
	_apals.push_back(new APAL(palette));
	_offs = new OFFS(_apals);
}

uint32_t WRAP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offs->getSize(); // offs
	for (int i = 0; i < _apals.size(); i++) // apals
		size += _apals[i]->getSize();
	return size;
}

void WRAP::write(fstream &f)
{
	IO::writeString(f, "WRAP");
	IO::writeU32BE(f, getSize());
	_offs->write(f);
	for (int i = 0; i < _apals.size(); i++)
		_apals[i]->write(f);
}

WRAP::~WRAP()
{
	delete _offs;

	for (int i = 0; i < _apals.size(); i++)
		delete _apals[i];
}

