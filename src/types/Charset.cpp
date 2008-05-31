#include "Charset.hpp"
#include "util/BMPFile.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Charset::N_COLORS = 15;
vector<Charset *> Charset::_instances;

Charset *Charset::getInstanceFromName(string charsetName)
{
	for (int i = 0; i < _instances.size(); i++)
		if (_instances[i]->getName() == charsetName)
			return _instances[i];
	return NULL;
}

Char::Char(XMLNode *node)
{
	Log::getInstance().write("Char\n");
	Log::getInstance().indent();

	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %u\n", _id);

	_x = node->getChild("x")->getIntegerContent();
	Log::getInstance().write("x: %u\n", _x);

	_y = node->getChild("y")->getIntegerContent();
	Log::getInstance().write("y: %u\n", _y);

	_width = node->getChild("width")->getIntegerContent();
	Log::getInstance().write("width: %u\n", _width);

	_height = node->getChild("height")->getIntegerContent();
	Log::getInstance().write("height: %u\n", _height);

	_xOffset = node->getChild("xOffset")->getIntegerContent();
	Log::getInstance().write("xOffset: %d\n", _xOffset);

	_yOffset = node->getChild("yOffset")->getIntegerContent();
	Log::getInstance().write("yOffset: %d\n", _yOffset);

	Log::getInstance().unIndent();
}

Charset::Charset(string dirName)
{
	Log::getInstance().write("Charset\n");
	Log::getInstance().indent();

	_instances.push_back(this);

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	BMPFile bmpFile(dirName + "charset.bmp");
	_width = bmpFile.getWidth();
	_height = bmpFile.getHeight();
	_bpp = bmpFile.getBPP();
	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(bmpFile.getPixel(i, j));
		_pixels.push_back(pixelColumn);
	}

	XMLFile xmlFile(dirName + "charset.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_id = _instances.size();
	Log::getInstance().write("id: %u\n", _id);

	_fontHeight = rootNode->getChild("fontHeight")->getIntegerContent();
	Log::getInstance().write("fontHeight: %u\n", _id);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("char", i++)) != NULL)
		_chars.push_back(new Char(child));

	string palette = rootNode->getChild("palette")->getStringContent();
	uint8_t indexA = 0, indexB = 0;
	for (int i = 0; i < N_COLORS; i++)
	{
		indexB = palette.find(' ', indexA);
		_palette.push_back(atoi(palette.substr(indexA, indexB).c_str()));
		indexA = indexB + 1;
	}

	Log::getInstance().unIndent();
}

Charset::~Charset()
{
	for (int i = 0; i < _chars.size(); i++)
		delete _chars[i];
}

