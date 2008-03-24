#include "WRAP5.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "OFFS.hpp"

const uint8_t WRAP5::STRIP_WIDTH = 8;

void saveAsPPM2(uint8_t **image, uint32_t width, uint32_t height, char *fileName)
{
	FILE *fp;
	if ((fp = fopen(fileName, "w")) == NULL)
		return;
	fprintf(fp, "P6\n%d %d\n255\n", width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			putc(image[j][i], fp);
			putc(image[j][i], fp);
			putc(image[j][i], fp);
		}
	fflush(fp);
	fclose(fp);
}

WRAP5::WRAP5(ifstream &f, uint32_t width, uint32_t height):
_offs(NULL),
_width(width),
_height(height)
{
	if (_width > 0)
	{
		_zPlane = new uint8_t *[_width];
		for (int i = 0; i < _width; i++)
			_zPlane[i] = new uint8_t[_height];
	}

	uint32_t basePos = (uint32_t)f.tellg() - 4;

	_size = IO::readU32BE(f);
	Log::getInstance().write("size: %d\n", _size);

	Log::getInstance().indent();

	string identifier = IO::readString(f, 4);
	Log::getInstance().write("%s\n", identifier.c_str());
	//_offs = new OFFS(f);

	for (int i = 0; i < _width / STRIP_WIDTH; i++)
		readStrip(f, &_zPlane[i * STRIP_WIDTH]);

	char fileName[50];
	sprintf(fileName, "zplanes/img_%d.ppm", (uint32_t)f.tellg());
	saveAsPPM2(_zPlane, _width, _height, fileName);

	Log::getInstance().unIndent();
}

void WRAP5::readStrip(ifstream &f, uint8_t **strip)
{
	uint8_t b;
	uint8_t c;
	uint32_t height = _height;
	while (height)
	{
		b = IO::readU8(f);
		if (b & 0x80)
		{
			b &= 0x7F;
			c = IO::readU8(f);
			do
			{
				for (int j = 0; j < STRIP_WIDTH; j++)
					strip[STRIP_WIDTH - j - 1][_height - height] = ((c >> j) & 0x01) * 255;
				height--;
			} while (--b && height);
		}
		else
		{
			do
			{
				c = IO::readU8(f);
				for (int j = 0; j < STRIP_WIDTH; j++)
					strip[STRIP_WIDTH - j - 1][_height - height] = ((c >> j) & 0x01 ) * 255;
				height--;
			}
			while (--b && height);
		}
	}
}

uint32_t WRAP5::getSize()
{
	uint32_t size = 0;
	return size;
}

void WRAP5::write(ofstream &f)
{
}

WRAP5::~WRAP5()
{
	if (_offs != NULL)
		delete _offs;

	if (_width > 0)
	{
		for (int i = 0; i < _width; i++)
			delete [] _zPlane[i];
		delete [] _zPlane;
	}
}

