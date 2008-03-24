#include "BOMP.hpp"
#include "util/IO.hpp"
#include "types/Image.hpp"
#include "WRAP.hpp"
#include "APAL.hpp"

BOMP::BOMP(Image *image)
{
	_width = image->getWidth();
	_height = image->getHeight();
	for (int i = 0; i < _height; i++)
	{
		vector<uint8_t> line;
		writeLine(line, image, i);
		_lengths.push_back(line.size());
		_lines.push_back(line);
	}
}

void BOMP::writeLine(vector<uint8_t> &line, Image *image, uint32_t y)
{
	uint8_t num;
	uint8_t code;
	uint32_t len = _width;
	uint32_t x = 0;
	while (len > 0)
	{
		num = 128;
		if (num > len)
			num = len;
		code = (num - 1) << 1;
		line.push_back(code);
		for (int i = 0; i < num; i++)
		{
			line.push_back(image->getPixel(x, y));
			x++;
		}
		len -= num;
	}
}

uint32_t BOMP::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // width
	size += sizeof(uint32_t); // height
	size += _lengths.size() * sizeof(uint16_t); // lengths
	for (int i = 0; i < _lines.size(); i++) // lines
		size += _lines[i].size() * sizeof(uint8_t);
	return size;
}

void BOMP::write(ofstream &f)
{
	uint32_t base = (uint32_t)f.tellp();
	IO::writeString(f, "BOMP");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, _width);
	IO::writeU32LE(f, _height);
	for (int i = 0; i < _height; i++)
	{
		IO::writeU16LE(f, _lengths[i]);
		for (int j = 0; j < _lines[i].size(); j++)
			IO::writeU8(f, _lines[i][j]);
	}
}

BOMP::~BOMP()
{
}

