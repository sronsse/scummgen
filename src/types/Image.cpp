#include "Image.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Palette.hpp"

const string Image::XML_FILE_NAME = "image.xml";

Image::Image():
_bitmapPath(""),
_paletteBaseIndex(0)
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

	_transparent = rootNode->getChild("transparent")->getBooleanContent();
	Log::write(LOG_INFO, "transparent: %s\n", _transparent ? "true" : "false");

	_bitmapPath = dirPath + rootNode->getChild("bitmapName")->getStringContent();
	Log::write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("zPlaneName", i++)) != NULL)
		_zPlanePaths.push_back(dirPath + child->getStringContent());

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

void Image::setPalette(Palette *palette, bool global)
{
	// Fill palette passed as a parameter
	_paletteBaseIndex = palette->add(_bitmapPath, !global);
}

Image::~Image()
{
}
