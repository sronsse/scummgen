#include "IMHD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"
#include "types/Image.hpp"

IMHD::IMHD(Object *object)
{
	_id = object->getID();
	_nImages = object->getNumberOfImages();
	_nZPlanesPerImage = object->getNumberOfZPlanesPerImage();
	_x = object->getImageX();
	_y = object->getImageY();
	_width = object->getImage(0)->getWidth();
	_height = object->getImage(0)->getHeight();
}

uint32_t IMHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint16_t); // id
	size += sizeof(uint16_t); // nImages
	size += sizeof(uint16_t); // nZPlanesPerImage
	size += sizeof(uint16_t); // unknown
	size += sizeof(uint16_t); // x
	size += sizeof(uint16_t); // y
	size += sizeof(uint16_t); // width
	size += sizeof(uint16_t); // height
	size += sizeof(uint16_t); // nHotspots
	return size;
}

void IMHD::write(ofstream &f)
{
	IO::writeString(f, "IMHD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _id);
	IO::writeU16LE(f, _nImages);
	IO::writeU16LE(f, _nZPlanesPerImage);
	IO::writeU16LE(f, 0);
	IO::writeU16LE(f, _x);
	IO::writeU16LE(f, _y);
	IO::writeU16LE(f, _width);
	IO::writeU16LE(f, _height);
	IO::writeU16LE(f, 0); // nHotspots
}

IMHD::~IMHD()
{
}

