#include "Image.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"

ZPlane::ZPlane(string fileName)
{
	Log::getInstance().write("ZPlane\n");
	Log::getInstance().indent();

	BMPFile bmpFile(fileName);

	_width = bmpFile.getWidth();
	Log::getInstance().write("width: %u\n", _width);

	_height = bmpFile.getHeight();
	Log::getInstance().write("height: %u\n", _height);

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

Image::Image(string dirName, string fileName, bool bomp, uint16_t nZPlanes)
{
	Log::getInstance().write("Image\n");
	Log::getInstance().indent();

	_bomp = bomp;
	Log::getInstance().write("bomp: %s\n", bomp ? "true" : "false");

	BMPFile bmpFile(dirName + fileName);

	_width = bmpFile.getWidth();
	Log::getInstance().write("width: %u\n", _width);

	_height = bmpFile.getHeight();
	Log::getInstance().write("height: %u\n", _height);

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

