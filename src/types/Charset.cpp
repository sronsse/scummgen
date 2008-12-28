#include "Charset.hpp"
#include "util/BMPFile.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Charset::N_COLORS = 15;

Char::Char(XMLNode *node)
{
	_id = node->getChild("id")->getIntegerContent();
	_x = node->getChild("x")->getIntegerContent();
	_y = node->getChild("y")->getIntegerContent();
	_width = node->getChild("width")->getIntegerContent();
	_height = node->getChild("height")->getIntegerContent();
	_xOffset = node->getChild("xOffset")->getIntegerContent();
	_yOffset = node->getChild("yOffset")->getIntegerContent();
}

Charset::Charset(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Charset\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	BMPFile bmpFile;
	bmpFile.open(dirName + "charset.bmp");
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

	XMLFile xmlFile;
	xmlFile.open(dirName + "charset.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	static uint16_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	_fontHeight = rootNode->getChild("fontHeight")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "fontHeight: %u\n", _fontHeight);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("char", i++)) != NULL)
		_chars.push_back(new Char(child));

	if (_chars.empty())
		Log::getInstance().write(LOG_ERROR, "Charset doesn't have any character !\n");

	/*string palette = rootNode->getChild("palette")->getStringContent();
	uint8_t indexA = 0, indexB = 0;
	for (int i = 0; i < N_COLORS; i++)
	{
		indexB = palette.find(' ', indexA);
		_palette.push_back(atoi(palette.substr(indexA, indexB).c_str()));
		indexA = indexB + 1;
	}*/
	for (int i = 0; i < N_COLORS; i++)
		_palette.push_back(i);

	Log::getInstance().unIndent();
}

Charset::~Charset()
{
	for (int i = 0; i < _chars.size(); i++)
		delete _chars[i];
}

