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

	getFrames(charset);
	calculateOffsets(charset);
}

void CHAR::getFrames(Charset *charset)
{
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
}

void CHAR::calculateOffsets(Charset *charset)
{
	// Prepare offsets list
	for (int i = 0; i < _nChars; i++)
		_offsets.push_back(0);

	// First "real" char offset is relative to the position of the BPP field
	_offsets[charset->getChar(0)->getID()] = sizeof(uint8_t); // bpp
	_offsets[charset->getChar(0)->getID()] += sizeof(uint8_t); // fontHeight
	_offsets[charset->getChar(0)->getID()] += sizeof(uint16_t); // nChars
	_offsets[charset->getChar(0)->getID()] += _nChars * sizeof(uint32_t); // offsets

	// We now calculate all the missing offsets according to the previous one
	for (int i = 1; i < _dataBytes.size(); i++)
	{
		_offsets[charset->getChar(i)->getID()] = _offsets[charset->getChar(i - 1)->getID()];
		_offsets[charset->getChar(i)->getID()] += sizeof(uint8_t); // width
		_offsets[charset->getChar(i)->getID()] += sizeof(uint8_t); // height
		_offsets[charset->getChar(i)->getID()] += sizeof(int8_t); // xOffset
		_offsets[charset->getChar(i)->getID()] += sizeof(int8_t); // yOffset
		_offsets[charset->getChar(i)->getID()] += _dataBytes[i - 1].size() * sizeof(uint8_t); // dataBytes
	}
}

void CHAR::getDataBytes(Charset *charset, Char *chr, vector<uint8_t> &dataBytes)
{
	uint32_t bytePos = 0;
	uint8_t bitPos = 0;
	for (int i = 0; i < chr->getHeight(); i++)
		for (int j = 0; j < chr->getWidth(); j++)
			IO::writeBits(dataBytes, charset->getPixel(chr->getX() + j, chr->getY() + i), bytePos, bitPos, _bpp);
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

void CHAR::write(fstream &f)
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
	for (int i = 0; i < _dataBytes.size(); i++)
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

