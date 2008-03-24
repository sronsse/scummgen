#include "BSTR.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "WRAP3.hpp"

BSTR::BSTR(Image *image)
{
	_wrap = new WRAP3(image);
}

uint32_t BSTR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _wrap->getSize(); // wrap
	return size;
}

void BSTR::write(ofstream &f)
{
	IO::writeString(f, "BSTR");
	IO::writeU32BE(f, getSize());
	_wrap->write(f);
}

BSTR::~BSTR()
{
	delete _wrap;
}

