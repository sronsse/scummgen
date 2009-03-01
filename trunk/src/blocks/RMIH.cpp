#include "RMIH.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"

RMIH::RMIH(Image *image)
{
	_nZPlanes = image->getNumberOfZPlanePaths();
}

uint32_t RMIH::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // nZPlanes
	return size;
}

void RMIH::write(fstream &f)
{
	IO::writeString(f, "RMIH");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _nZPlanes);
}

RMIH::~RMIH()
{
}
