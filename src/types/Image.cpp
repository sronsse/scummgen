#include "Image.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Palette.hpp"

Image::Image():
_bitmapPath(""),
_paletteBaseIndex(0)
{
}

void Image::load(string dirPath, Palette *palette, bool global)
{
	Log::getInstance().write(LOG_INFO, "Image\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "image.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_bitmapPath = dirPath + rootNode->getChild("bitmapName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("zPlaneName", i++)) != NULL)
		_zPlanePaths.push_back(dirPath + child->getStringContent());

	_paletteBaseIndex = palette->add(_bitmapPath, !global);

	Log::getInstance().unIndent();
}

Image::~Image()
{
}
