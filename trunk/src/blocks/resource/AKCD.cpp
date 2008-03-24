#include "AKCD.hpp"
#include "util/IO.hpp"
#include "types/Costume.hpp"

AKCD::AKCD(Costume *costume)
{
	// The BOMP codec is the only one implemented 
	_offsets.push_back(0);
	for (int i = 0; i < costume->getNumberOfFrames(); i++)
	{
		uint32_t offset = 0;
		for (int j = 0; j < costume->getFrame(i)->getHeight(); j++)
		{
			vector<uint8_t> line;
			uint8_t num;
			uint8_t code;
			uint32_t len = costume->getFrame(i)->getWidth();
			uint32_t x = 0;
			while (len > 0)
			{
				num = 128;
				if (num > len)
					num = len;
				code = (num - 1) << 1;
				line.push_back(code);
				for (int k = 0; k < num; k++)
				{
					line.push_back(costume->getFrame(i)->getPixel(x, j));
					x++;
				}
				len -= num;
			}
			offset += sizeof(uint16_t) + line.size() * sizeof(uint8_t); // length and pixels
			_lengths.push_back(line.size());
			_lines.push_back(line);
		}
		if (i != costume->getNumberOfFrames() - 1)
			_offsets.push_back(_offsets[_offsets.size() - 1] + offset);
	}
}

uint32_t AKCD::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += _lengths.size() * sizeof(uint16_t); // lengths
	for (int i = 0; i < _lines.size(); i++) // lines
		size += _lines[i].size() * sizeof(uint8_t);
	return size;
}

void AKCD::write(ofstream &f)
{
	IO::writeString(f, "AKCD");
	IO::writeU32BE(f, getSize());
	for (int i = 0; i < _lengths.size(); i++)
	{
		IO::writeU16LE(f, _lengths[i]);
		for (int j = 0; j < _lines[i].size(); j++)
			IO::writeU8(f, _lines[i][j]);
	}
}

AKCD::~AKCD()
{
}

