#include "RMIM.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "RMIH.hpp"
#include "IMxx.hpp"

RMIM::RMIM(Image *image)
{
	_rmih = new RMIH(image);
	_im00 = new IMxx(image, 0);
}

uint32_t RMIM::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _rmih->getSize(); // rmih
	size += _im00->getSize(); // im00
	return size;
}

void RMIM::write(fstream &f)
{
	IO::writeString(f, "RMIM");
	IO::writeU32BE(f, getSize());
	_rmih->write(f);
	_im00->write(f);
}

RMIM::~RMIM()
{
	delete _rmih;
	delete _im00;
}

