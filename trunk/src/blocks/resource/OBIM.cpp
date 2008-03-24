#include "OBIM.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"
#include "IMHD.hpp"
#include "IMAG.hpp"

OBIM::OBIM(Object *object):
_imag(NULL)
{
	_imhd = new IMHD(object);
	if (object->getNumberOfImages() > 0)
		_imag = new IMAG(object);
}

uint32_t OBIM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _imhd->getSize(); // imhd
	if (_imag)
		size += _imag->getSize(); // imag
	return size;
}

void OBIM::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "OBIM");
	IO::writeU32BE(f, getSize());
	_imhd->write(f);
	if (_imag)
		_imag->write(f);
}

OBIM::~OBIM()
{
	delete _imhd;

	if (_imag != NULL)
		delete _imag;
}

