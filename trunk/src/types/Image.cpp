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

	_pixels = new uint8_t *[_width];
	for (int i = 0; i < _width; i++)
	{
		_pixels[i] = new uint8_t[_height];
		for (int j = 0; j < _height; j++)
			_pixels[i][j] = bmpFile.getPixel(i, j);
	}

	Log::getInstance().unIndent();
}

ZPlane::~ZPlane()
{
	for (int i = 0; i < _width; i++)
		delete [] _pixels[i];
	delete [] _pixels;
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

	_pixels = new uint8_t *[_width];
	for (int i = 0; i < _width; i++)
	{
		_pixels[i] = new uint8_t[_height];
		for (int j = 0; j < _height; j++)
			_pixels[i][j] = bmpFile.getPixel(i, j);
	}

	for (int i = 0; i < nZPlanes; i++)
		_zPlanes.push_back(new ZPlane(dirName + "zplanes/zplane_" + IO::getStringFromIndex(i, 3) + ".bmp"));

	Log::getInstance().unIndent();
}

Image::~Image()
{
	for (int i = 0; i < _width; i++)
		delete [] _pixels[i];
	delete [] _pixels;

	for (int i = 0; i < _zPlanes.size(); i++)
		delete _zPlanes[i];
}

