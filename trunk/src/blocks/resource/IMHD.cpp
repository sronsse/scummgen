#include "IMHD.hpp"
#include "util/IO.hpp"
#include "types/Object.hpp"

const uint8_t IMHD::N_CHARS = 32;
const uint32_t IMHD::VERSION = 801;
const uint32_t IMHD::UNKNOWN1 = 0;
const uint32_t IMHD::UNKNOWN2 = 0;
const uint32_t IMHD::UNKNOWN3 = 0;
const uint32_t IMHD::UNKNOWN4 = 0;

IMHD::IMHD(Object *object)
{
	_name = object->getName();
	_name.resize(N_CHARS, '\0');
	_nImages = object->getNumberOfImages();
	_x = object->getX();
	_y = object->getY();
	_width = object->getWidth();
	_height = object->getHeight();
	_hotSpotXs.push_back(object->getHotSpotX());
	_hotSpotYs.push_back(object->getHotSpotY());
}

uint32_t IMHD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += N_CHARS * sizeof(uint8_t); // name
	size += sizeof(uint32_t); // unknown
	size += sizeof(uint32_t); // unknown
	size += sizeof(uint32_t); // version
	size += sizeof(uint32_t); // nImages
	size += sizeof(uint32_t); // x
	size += sizeof(uint32_t); // y
	size += sizeof(uint32_t); // width
	size += sizeof(uint32_t); // height
	size += sizeof(uint32_t); // unknown actorDir ?
	size += sizeof(uint32_t); // unknown flags ?
	size += _hotSpotXs.size() * sizeof(uint32_t); // hotSpotXs
	size += _hotSpotYs.size() * sizeof(uint32_t); // hotSpotYs
	return size;
}

void IMHD::write(ofstream &f)
{
	IO::writeString(f, "IMHD");
	IO::writeU32BE(f, getSize());
	IO::writeString(f, _name);
	IO::writeU32LE(f, UNKNOWN1);
	IO::writeU32LE(f, UNKNOWN2);
	IO::writeU32LE(f, VERSION);
	IO::writeU32LE(f, _nImages);
	IO::writeU32LE(f, _x);
	IO::writeU32LE(f, _y);
	IO::writeU32LE(f, _width);
	IO::writeU32LE(f, _height);
	IO::writeU32LE(f, UNKNOWN3);
	IO::writeU32LE(f, UNKNOWN4);
	for (int i = 0; i < _hotSpotXs.size(); i++)
	{
		IO::writeU32LE(f, _hotSpotXs[i]);
		IO::writeU32LE(f, _hotSpotYs[i]);
	}
}

IMHD::~IMHD()
{
}

