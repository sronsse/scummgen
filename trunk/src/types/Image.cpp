#include "Image.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Palette.hpp"

const string Image::XML_FILE_NAME = "image.xml";

Image::Image():
_name(""),
_transparent(false),
_bitmapPath(""),
_width(0),
_height(0)
{
}

void Image::load(string dirPath)
{
	Log::write(LOG_INFO, "Image\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_bitmapPath = dirPath + rootNode->getChild("bitmapName")->getStringContent();
	Log::write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("zPlaneName", i++)) != NULL)
		_zPlanePaths.push_back(dirPath + child->getStringContent());

	// Get width and height from bitmap
	BMPFile bmpFile;
	bmpFile.open(_bitmapPath);
	_width = bmpFile.getWidth();
	_height = bmpFile.getHeight();

	Log::unIndent();
}

void Image::save(string dirPath)
{
	Log::write(LOG_INFO, "Image\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("image");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	string bitmapName = _bitmapPath.substr(_bitmapPath.find_last_of('/') + 1);
	rootNode->addChild(new XMLNode("bitmapName", bitmapName));
	string newBitmapPath = dirPath + bitmapName;
	if (_bitmapPath != newBitmapPath)
	{
		if (!IO::copyFile(_bitmapPath, newBitmapPath))
			Log::write(LOG_ERROR, "Could not copy file \"%s\" to \"%s\" !\n", _bitmapPath.c_str(), newBitmapPath.c_str());
		_bitmapPath = newBitmapPath;
	}
	Log::write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	for (int i = 0; i < _zPlanePaths.size(); i++)
	{
		string zPlaneName = _zPlanePaths[i].substr(_zPlanePaths[i].find_last_of('/') + 1);
		rootNode->addChild(new XMLNode("zPlaneName", zPlaneName));
		string newZPlanePath = dirPath + zPlaneName;
		if (_zPlanePaths[i] != newZPlanePath)
		{
			if (!IO::copyFile(_zPlanePaths[i], newZPlanePath))
				Log::write(LOG_ERROR, "Could not copy file \"%s\" to \"%s\" !\n", _zPlanePaths[i].c_str(), newZPlanePath.c_str());
			_zPlanePaths[i] = newZPlanePath;
		}
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save image to the specified directory !\n");

	Log::unIndent();
}

void Image::prepare(Palette *palette, PaletteData *paletteData)
{
	Log::write(LOG_INFO, "Preparing image \"%s\"...\n", _name.c_str());
	Log::indent();

	// Set transparency
	_transparent = paletteData->isTransparent();

	// Open original bitmap
	BMPFile bmpFile;
	bmpFile.open(_bitmapPath);

	// Get original palette from bitmap
	vector<Color> colors;
	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		colors.push_back(bmpFile.getColor(i));

	// Clear our pixel array
	_pixels.clear();

	// Get pixels from bitmap
	for (int x = 0; x < _width; x++)
	{
		vector<uint8_t> pixelColumn;
		for (int y = 0; y < _height; y++)
			pixelColumn.push_back(bmpFile.getPixel(x, y));
		_pixels.push_back(pixelColumn);
	}

	// Add colors to palette (and update pixels)
	palette->add(&colors, _pixels, paletteData);

	Log::write(LOG_INFO, "Palette cursor: %u\n", palette->getCursor());
	Log::unIndent();
}

Image::~Image()
{
}
