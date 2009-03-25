#include "Charset.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

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

Charset::Charset():
_id(0),
_name(""),
_bitmapPath(""),
_fontHeight(0)
{
}

void Charset::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Charset\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "charset.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_bitmapPath = dirPath + rootNode->getChild("bitmapName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	_fontHeight = rootNode->getChild("fontHeight")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "fontHeight: %u\n", _fontHeight);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("char", i++)) != NULL)
	{
		Char *chr = new Char();
		chr->load(child);
		_chars.push_back(chr);
	}

	if (_chars.empty())
		Log::getInstance().write(LOG_ERROR, "Charset doesn't contain any character !\n");

	Log::getInstance().unIndent();
}

Charset::~Charset()
{
	for (int i = 0; i < _chars.size(); i++)
		delete _chars[i];
}
