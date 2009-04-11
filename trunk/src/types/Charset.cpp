#include "Charset.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string Charset::XML_FILE_NAME = "charset.xml";

Char::Char():
_id(0),
_x(0),
_y(0),
_width(0),
_height(0),
_xOffset(0),
_yOffset(0)
{
}

void Char::load(XMLNode *node)
{
	_id = node->getChild("id")->getIntegerContent();
	_x = node->getChild("x")->getIntegerContent();
	_y = node->getChild("y")->getIntegerContent();
	_width = node->getChild("width")->getIntegerContent();
	_height = node->getChild("height")->getIntegerContent();
	_xOffset = node->getChild("xOffset")->getIntegerContent();
	_yOffset = node->getChild("yOffset")->getIntegerContent();
}

void Char::save(XMLNode *node)
{
	node->addChild(new XMLNode("id", _id));
	node->addChild(new XMLNode("x", _x));
	node->addChild(new XMLNode("y", _y));
	node->addChild(new XMLNode("width", _width));
	node->addChild(new XMLNode("height", _height));
	node->addChild(new XMLNode("xOffset", _xOffset));
	node->addChild(new XMLNode("yOffset", _yOffset));
}

Charset::Charset():
_id(0),
_name(""),
_bitmapPath(""),
_fontHeight(0)
{
}

void Charset::load(string dirPath)
{
	Log::write(LOG_INFO, "Charset\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	_bitmapPath = dirPath + rootNode->getChild("bitmapName")->getStringContent();
	Log::write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	_fontHeight = rootNode->getChild("fontHeight")->getIntegerContent();
	Log::write(LOG_INFO, "fontHeight: %u\n", _fontHeight);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("char", i++)) != NULL)
	{
		Char *chr = new Char();
		chr->load(child);
		_chars.push_back(chr);
	}

	Log::unIndent();
}

void Charset::save(string dirPath)
{
	Log::write(LOG_INFO, "Charset\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("charset");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	rootNode->addChild(new XMLNode("description", _description));
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

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
	

	rootNode->addChild(new XMLNode("fontHeight", _fontHeight));
	Log::write(LOG_INFO, "fontHeight: %u\n", _fontHeight);

	for (int i = 0; i < _chars.size(); i++)
	{
		XMLNode *child = new XMLNode("char"); 
		rootNode->addChild(child);
		_chars[i]->save(child);
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save charset to the specified directory !\n");

	Log::unIndent();
}

Charset::~Charset()
{
	for (int i = 0; i < _chars.size(); i++)
		delete _chars[i];
}
