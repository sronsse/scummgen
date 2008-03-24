#include "IMAG.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "types/Object.hpp"
#include "WRAP2.hpp"

IMAG::IMAG(Image *image)
{
	_wrap = new WRAP2(image);
}

IMAG::IMAG(Object *object)
{
	_wrap = new WRAP2(object);
}

uint32_t IMAG::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _wrap->getSize(); // wrap
	return size;
}

void IMAG::write(ofstream &f)
{
	IO::writeString(f, "IMAG");
	IO::writeU32BE(f, getSize());
	_wrap->write(f);
}

IMAG::~IMAG()
{
	delete _wrap;
}

