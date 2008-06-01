#include "CHAR.hpp"
#include "util/IO.hpp"
#include "types/Charset.hpp"

const int CHAR::N_COLORS = 15;
const int CHAR::MAGIC_NUMBER_SIZE = 23;
const int CHAR::MAGIC_NUMBER_UNKNOWN = 0x0363;

CHAR::CHAR(Charset *charset)
{
	for (int i = 0; i < N_COLORS; i++)
		_palette.push_back(charset->getPaletteIndex(i));
	_bpp = charset->getBPP();
	_fontHeight = charset->getFontHeight();
	_nChars = 0;
	for (int i = 0; i < charset->getNumberOfChars(); i++)
		if (charset->getChar(i)->getID() + 1 > _nChars)
			_nChars = charset->getChar(i)->getID() + 1;
	for (int i = 0; i < _nChars; i++)
		_offsets.push_back(0);
	for (int i = 0; i < charset->getNumberOfChars(); i++)
	{
		_widths.push_back(charset->getChar(i)->getWidth());
		_heights.push_back(charset->getChar(i)->getHeight());
		_xOffsets.push_back(charset->getChar(i)->getXOffset());
		_yOffsets.push_back(charset->getChar(i)->getYOffset());
		vector<uint8_t> dataBytes;
		getDataBytes(charset, charset->getChar(i), dataBytes);
		_dataBytes.push_back(dataBytes);
	}
	// First "real" char offset is relative to the position of the BPP field
	_offsets[charset->getChar(0)->getID()] = sizeof(uint8_t); // bpp
	_offsets[charset->getChar(0)->getID()] += sizeof(uint8_t); // fontHeight
	_offsets[charset->getChar(0)->getID()] += sizeof(uint16_t); // nChars
	_offsets[charset->getChar(0)->getID()] += _nChars * sizeof(uint32_t); // offsets
	// We now calculate all the missing offsets according to the previous one
	for (int i = 1; i < _widths.size(); i++)
	{
		_offsets[charset->getChar(i)->getID()] = _offsets[charset->getChar(i - 1)->getID()];
		_offsets[charset->getChar(i)->getID()] += sizeof(uint8_t); // width
		_offsets[charset->getChar(i)->getID()] += sizeof(uint8_t); // height
		_offsets[charset->getChar(i)->getID()] += sizeof(int8_t); // xOffset
		_offsets[charset->getChar(i)->getID()] += sizeof(int8_t); // yOffset
		_offsets[charset->getChar(i)->getID()] += _dataBytes[i].size() * sizeof(uint8_t); // dataBytes
	}
}

void CHAR::getDataBytes(Charset *charset, Char *chr, vector<uint8_t> &dataBytes)
{
	// This is SCUMM's way of calculating the number of bytes for pixel storage
	// There are cases where an extra byte is added for no reason though
	// (when _width * _height * bpp % 8 == 0)
	uint16_t nDataBytes = (chr->getWidth() * chr->getHeight() * _bpp) / 8 + 1;
	for (int i = 0; i < nDataBytes; i++)
		dataBytes.push_back(0);

	// Bits are written from left to right (MSB first)
	uint16_t bytePos = 0;
	uint8_t bitPos = 7;
	for (int i = 0; i < chr->getHeight(); i++)
		for (int j = 0; j < chr->getWidth(); j++)
			for (int k = 0; k < _bpp; k++)
			{
				dataBytes[bytePos] |= ((charset->getPixel(chr->getX() + j, chr->getY() + i) >> k) & 0x1) << bitPos;
				if (bitPos == 0)
				{
					bytePos++;
					bitPos = 7;
				}
				else bitPos--;
			}
}

uint32_t CHAR::getSize()
{
	uint32_t size = 0;
	size += 4 * sizeof(uint8_t); // identifier
	size += sizeof(uint32_t); // size
	size += sizeof(uint32_t); // size - MAGIC_NUMBER_SIZE
	size += sizeof(uint16_t); // MAGIC_NUMBER_UNKNOWN
	size += N_COLORS * sizeof(uint8_t); // palette
	size += sizeof(uint8_t); // bpp
	size += sizeof(uint8_t); // fontHeight
	size += sizeof(uint16_t); // nChars
	size += _offsets.size() * sizeof(uint32_t); // offsets
	for (int i = 0; i < _widths.size(); i++) // chars
	{
		size += sizeof(uint8_t); // width
		size += sizeof(uint8_t); // height
		size += sizeof(int8_t); // xOffset
		size += sizeof(int8_t); // yOffsets
		size += _dataBytes[i].size() * sizeof(uint8_t); // dataBytes
	}
	return size;
}

void CHAR::write(ofstream &f)
{
	IO::writeString(f, "CHAR");
	IO::writeU32BE(f, getSize());
	IO::writeU32LE(f, getSize() - MAGIC_NUMBER_SIZE);
	IO::writeU16LE(f, MAGIC_NUMBER_UNKNOWN);
	for (int i = 0; i < N_COLORS; i++)
		IO::writeU8(f, _palette[i]);
	IO::writeU8(f, _bpp);
	IO::writeU8(f, _fontHeight);
	IO::writeU16LE(f, _nChars);
	for (int i = 0; i < _nChars; i++)
		IO::writeU32LE(f, _offsets[i]);
	for (int i = 0; i < _widths.size(); i++)
	{
		IO::writeU8(f, _widths[i]);
		IO::writeU8(f, _heights[i]);
		IO::writeU8(f, _xOffsets[i]);
		IO::writeU8(f, _yOffsets[i]);
		for (int j = 0; j < _dataBytes[i].size(); j++)
			IO::writeU8(f, _dataBytes[i][j]);
	}
}

CHAR::~CHAR()
{
}

