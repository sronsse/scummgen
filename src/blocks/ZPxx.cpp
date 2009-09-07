#include "ZPxx.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"

const uint8_t ZPxx::STRIP_WIDTH = 8;
const uint8_t ZPxx::MAX_BYTES = 0x7F;

ZPxx::ZPxx(string filePath, uint8_t index)
{
	BMPFile bmpFile;
	bmpFile.open(filePath);
	_index = index;
	for (int i = 0; i < bmpFile.getWidth() / STRIP_WIDTH; i++)
	{
		vector<uint8_t> strip;
		uint16_t h = bmpFile.getHeight();
		while (h > 0)
		{
			uint8_t nBytes = h > MAX_BYTES ? MAX_BYTES : h;
			strip.push_back(nBytes);
			for (int j = 0; j < nBytes; j++)
			{
				uint8_t byte = 0;
				for (int k = 0; k < STRIP_WIDTH; k++)
					byte |= bmpFile.getPixel(i * STRIP_WIDTH + k, bmpFile.getHeight() - h) << (STRIP_WIDTH - 1 - k);
				strip.push_back(byte);
				h--;
			}
		}
		_strips.push_back(strip);
	}
	uint16_t firstOffset = 0;
	firstOffset += 4 * sizeof(uint8_t); // identifier
	firstOffset += sizeof(uint32_t); // size
	firstOffset += _strips.size() * sizeof(uint16_t); // offsets
	_offsets.push_back(firstOffset);
	for (int i = 1; i < _strips.size(); i++)
		_offsets.push_back(_offsets[i - 1] + _strips[i - 1].size());
}

uint32_t ZPxx::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _offsets.size() * sizeof(uint16_t); // offsets
	for (int i = 0; i < _strips.size(); i++) // strips
		size += _strips[i].size() * sizeof(uint8_t);
	return size;
}

void ZPxx::write(fstream &f)
{
	char identifier[5];
	snprintf(identifier, 5, "ZP%02u", _index);
	IO::writeString(f, identifier);
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _offsets.size(); i++)
		IO::writeU16LE(f, _offsets[i]);
	for (int i = 0; i < _strips.size(); i++)
		for (int j = 0; j < _strips[i].size(); j++)
			IO::writeU8(f, _strips[i][j]);
}

ZPxx::~ZPxx()
{
}
