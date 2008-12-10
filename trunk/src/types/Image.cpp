#include "Image.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

ZPlane::ZPlane(string fileName)
{
	Log::getInstance().write(LOG_INFO, "ZPlane\n");
	Log::getInstance().indent();

	BMPFile bmpFile;
	bmpFile.open(fileName);

	_width = bmpFile.getWidth();
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);

	_height = bmpFile.getHeight();
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(bmpFile.getPixel(i, j));
		_pixels.push_back(pixelColumn);
	}

	Log::getInstance().unIndent();
}

ZPlane::~ZPlane()
{
}

Image::Image(string dirName, string fileName, uint16_t nZPlanes)
{
	Log::getInstance().write(LOG_INFO, "Image\n");
	Log::getInstance().indent();

	BMPFile bmpFile;
	bmpFile.open(dirName + fileName);

	_width = bmpFile.getWidth();
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);

	_height = bmpFile.getHeight();
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		_colors.push_back(bmpFile.getColor(i));

	_paletteBaseIndex = 0;
	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(bmpFile.getPixel(i, j));
		_pixels.push_back(pixelColumn);
	}

	for (int i = 0; i < nZPlanes; i++)
		_zPlanes.push_back(new ZPlane(dirName + "zplanes/zplane_" + IO::getStringFromIndex(i, 3) + ".bmp"));

	Log::getInstance().unIndent();
}

Image::~Image()
{
	for (int i = 0; i < _zPlanes.size(); i++)
		delete _zPlanes[i];
}

