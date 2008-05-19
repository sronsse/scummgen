#include "SMAP.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"

const uint8_t SMAP::STRIP_WIDTH = 8;
const uint8_t SMAP::CID_NO_COMPRESSION = 0x01;

SMAP::SMAP(Image *image)
{
	for (int i = 0; i < image->getWidth() / STRIP_WIDTH; i++)
	{
		vector<uint8_t> strip;
		strip.push_back(CID_NO_COMPRESSION);
		for (int j = 0; j < image->getHeight(); j++)
			for (int k = 0; k < STRIP_WIDTH; k++)
				strip.push_back(image->getPixel(i * STRIP_WIDTH + k, j));
		_strips.push_back(strip);
	}
	uint32_t firstOffset = 4 * sizeof(uint8_t) + sizeof(uint32_t) + _strips.size() * sizeof(uint32_t);
	_offsets.push_back(firstOffset);
	for (int i = 1; i < _strips.size(); i++)
		_offsets.push_back(_offsets[i - 1] + _strips[i - 1].size());
}

uint32_t SMAP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offsets.size() * sizeof(uint32_t); // offsets
	for (int i = 0; i < _strips.size(); i++) // strips
		size += _strips[i].size() * sizeof(uint8_t);
	return size;
}

void SMAP::write(ofstream &f)
{
	IO::writeString(f, "SMAP");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _offsets.size(); i++)
		IO::writeU32LE(f, _offsets[i]);
	for (int i = 0; i < _strips.size(); i++)
		for (int j = 0; j < _strips[i].size(); j++)
			IO::writeU8(f, _strips[i][j]);
}

SMAP::~SMAP()
{
}

