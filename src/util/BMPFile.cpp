#include "BMPFile.hpp"
#include <fstream>

const uint8_t BMPFile::BI_RGB = 0;
const uint8_t BMPFile::N_CHANNELS = 3;

BMPFile::BMPFile(string fileName)
{
	// We open the file, which should be an indexed BMP file
	ifstream file(fileName.c_str(), ios::in | ios::binary);
	if (!file.is_open())
		return;

	uint16_t identifier;
	file.read((char *)&identifier, 2);

	uint32_t fileSize;
	file.read((char *)&fileSize, 4);

	uint32_t reserved;
	file.read((char *)&reserved, 4);

	uint32_t bitmapDataOffset;
	file.read((char *)&bitmapDataOffset, 4);

	uint32_t bitmapHeaderSize;
	file.read((char *)&bitmapHeaderSize, 4);

	file.read((char *)&_width, 4);

	file.read((char *)&_height, 4);

	uint16_t nPlanes;
	file.read((char *)&nPlanes, 2);

	file.read((char *)&_bpp, 2);
	// The number of bits per pixel cannot be above 8
	if (_bpp > 8)
	{
		file.close();
		return;
	}

	uint32_t compression;
	file.read((char *)&compression, 4);
	// We support only non-encoded BMP files
	if (compression != BI_RGB)
	{
		file.close();
		return;
	}
	uint32_t bitmapDataSize;
	file.read((char *)&bitmapDataSize, 4);

	uint32_t hResolution;
	file.read((char *)&hResolution, 4);

	uint32_t vResolution;
	file.read((char *)&vResolution, 4);

	uint32_t nColors;
	file.read((char *)&nColors, 4);

	uint32_t nImportantColors;
	file.read((char *)&nImportantColors, 4);

	uint8_t r, g, b, unused;
	for (int i = 0; i < nColors; i++)
	{
		file.read((char *)&r, 1);
		file.read((char *)&g, 1);
		file.read((char *)&b, 1);
		file.read((char *)&unused, 1);
		_colors.push_back(r);
		_colors.push_back(g);
		_colors.push_back(b);
	}

	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(0);
		_pixels.push_back(pixelColumn);
	}

	// Decoding pixel data
	uint8_t bitPos = 7, byte;
	uint8_t modulo = (_width * _bpp) % 32;
	for (int i = _height - 1; i >= 0; i--)
	{
		for (int j = 0; j < _width; j++)
			for (int k = _bpp - 1; k >= 0; k--)
			{
				if (bitPos == 7)
					file.read((char *)&byte, 1);
				_pixels[j][i] |= ((byte >> bitPos) & 0x1) << k;
				if (bitPos == 0)
					bitPos = 7;
				else
					bitPos--;
			}
		
		if (modulo != 0)
			for (int j = 0; j < (32 - modulo) / 8; j++)
				file.read((char *)&unused, 1);
 	}

	file.close();
}

BMPFile::~BMPFile()
{
}

