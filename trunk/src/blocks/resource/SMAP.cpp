#include "SMAP.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "BSTR.hpp"
#include "ZPLN.hpp"

SMAP::SMAP(Image *image):
_zpln(NULL)
{
	_bstr = new BSTR(image);
}

uint32_t SMAP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	if (_bstr)
		size += _bstr->getSize(); // bstr
	if (_zpln)
		size += _zpln->getSize(); // zpln
	return size;
}

void SMAP::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "SMAP");
	IO::writeU32BE(f, getSize());
	if (_bstr)
		_bstr->write(f);
	if (_zpln)
		_zpln->write(f);
}

SMAP::~SMAP()
{
	if (_bstr != NULL)
		delete _bstr;
	if (_zpln != NULL)
		delete _zpln;
}

