#include "IMHD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"
#include "types/Image.hpp"

const uint16_t IMHD::UNKNOWN = 0;
const uint16_t IMHD::X = 0;
const uint16_t IMHD::Y = 0;

IMHD::IMHD(Object *object)
{
	_id = object->getID();
	_nImages = object->getNumberOfImages();
	_nZPlanesPerImage = _nImages == 0 ? 0 : object->getImage(0)->getNumberOfZPlanePaths();

	if (_nImages == 0)
	{
		_width = 0;
		_height = 0;
	}
	else
	{
		_width = object->getImage(0)->getWidth();
		_height = object->getImage(0)->getHeight();
	}

	// Only one hotspot is now supported
	_hotspotXs.push_back(object->getHotspotX());
	_hotspotYs.push_back(object->getHotspotY());
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
	size += _hotspotXs.size() * sizeof(int16_t); // hotspotXs
	size += _hotspotYs.size() * sizeof(int16_t); // hotspotYs
	return size;
}

void IMHD::write(fstream &f)
{
	IO::writeString(f, "IMHD");
	IO::writeU32BE(f, getSize());
	IO::writeU16LE(f, _id);
	IO::writeU16LE(f, _nImages);
	IO::writeU16LE(f, _nZPlanesPerImage);
	IO::writeU16LE(f, UNKNOWN);
	IO::writeU16LE(f, X);
	IO::writeU16LE(f, Y);
	IO::writeU16LE(f, _width);
	IO::writeU16LE(f, _height);
	IO::writeU16LE(f, _hotspotXs.size());
	for (int i = 0; i < _hotspotXs.size(); i++)
	{
		IO::writeU16LE(f, _hotspotXs[i]);
		IO::writeU16LE(f, _hotspotYs[i]);
	}
}

IMHD::~IMHD()
{
}
