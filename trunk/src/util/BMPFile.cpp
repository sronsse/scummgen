#include "BMPFile.hpp"
#include <fstream>
#include "IO.hpp"
#include "Log.hpp"

const uint8_t BMPFile::BI_RGB = 0;

BMPFile::BMPFile()
{
}

bool BMPFile::open(string fileName)
{
	// We open the file, which should be an indexed BMP file
	fstream file(fileName.c_str(), ios::in | ios::binary);
	if (!file.is_open())
		return false;

	uint16_t identifier = IO::readU16LE(file);
	uint32_t fileSize = IO::readU32LE(file);
	uint32_t reserved = IO::readU32LE(file);

	uint32_t bitmapDataOffset = IO::readU32LE(file);
	uint32_t bitmapHeaderSize = IO::readU32LE(file);

	_width = IO::readU32LE(file);
	_height = IO::readU32LE(file);

	uint16_t nPlanes = IO::readU16LE(file);
	
	// The number of bits per pixel cannot be above 8
	_bpp = IO::readU16LE(file);
	if (_bpp > 8)
	{
		file.close();
		return false;
	}

	// Only non-encoded BMP files are supported
	uint32_t compression = IO::readU32LE(file);
	if (compression != BI_RGB)
	{
		file.close();
		return false;
	}

	uint32_t bitmapDataSize = IO::readU32LE(file);
	uint32_t hResolution = IO::readU32LE(file);
	uint32_t vResolution = IO::readU32LE(file);
	uint32_t nColors = IO::readU32LE(file);
	uint32_t nImportantColors = IO::readU32LE(file);

	Color color;
	for (int i = 0; i < nColors; i++)
	{
		color.b = IO::readU8(file);
		color.g = IO::readU8(file);
		color.r = IO::readU8(file);
		IO::readU8(file);
		_colors.push_back(color);
	}

	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(0);
		_pixels.push_back(pixelColumn);
	}

	// Decoding pixel data
	uint8_t padding = 32 - (_width * _bpp) % 32;
	if (padding == 32)
		padding = 0;
	for (int i = _height - 1; i >= 0; i--)
	{
		uint8_t byte;
		uint8_t bitPos = 0;
		for (int j = 0; j < _width; j++)
			_pixels[j][i] = IO::readBits(file, byte, bitPos, _bpp);
		bitPos = 0;
		IO::readBits(file, byte, bitPos, padding);
	}

	file.close();
	return true;
}

BMPFile::~BMPFile()
{
}

