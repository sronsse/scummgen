#include "Costume.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const int Costume::N_LIMBS = 16;

Limb::Limb(XMLNode *node)
{
	Log::getInstance().write("Limb\n");
	Log::getInstance().indent();

	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %d\n", _id);

	_start = node->getChild("start")->getIntegerContent();
	Log::getInstance().write("start: %d\n", _start);

	_length = node->getChild("length")->getIntegerContent();
	Log::getInstance().write("length: %d\n", _length);

	_loop = node->getChild("loop")->getBooleanContent();
	Log::getInstance().write("loop: %d\n", _loop);

	Log::getInstance().unIndent();
}

Limb::~Limb()
{
}

Anim::Anim(XMLNode *node)
{
	Log::getInstance().write("Anim\n");
	Log::getInstance().indent();

	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %d\n", _id);

	_mask = node->getChild("mask")->getIntegerContent();
	Log::getInstance().write("mask: %x\n", _mask);

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("limb", i++)) != NULL)
		_limbs.push_back(new Limb(child));

	Log::getInstance().unIndent();
}

Anim::~Anim()
{
	for (int i = 0; i < _limbs.size(); i++)
		delete _limbs[i];
}

Frame::Frame(XMLNode *node, string fileName)
{
	Log::getInstance().write("Frame\n");
	Log::getInstance().indent();

	BMPFile bmpFile(fileName);
	Log::getInstance().write("fileName: %s\n", fileName.c_str());

	_width = bmpFile.getWidth();
	Log::getInstance().write("width: %d\n", _width);

	_height = bmpFile.getHeight();
	Log::getInstance().write("height: %d\n", _height);

	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(bmpFile.getPixel(i, j));
		_pixels.push_back(pixelColumn);
	}

	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %d\n", _id);

	_x = node->getChild("x")->getIntegerContent();
	Log::getInstance().write("x: %d\n", _x);

	_y = node->getChild("y")->getIntegerContent();
	Log::getInstance().write("y: %d\n", _y);

	_xInc = node->getChild("xInc")->getIntegerContent();
	Log::getInstance().write("xInc: %d\n", _xInc);

	_yInc = node->getChild("yInc")->getIntegerContent();
	Log::getInstance().write("yInc: %d\n", _yInc);

	Log::getInstance().unIndent();
}

Frame::~Frame()
{
}

Costume::Costume(string dirName)
{
	Log::getInstance().write("Costume\n");
	Log::getInstance().indent();

	XMLFile xmlFile(dirName + "costume.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_id = rootNode->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %d\n", _id);

	_mirror = rootNode->getChild("mirror")->getBooleanContent();
	Log::getInstance().write("mirror: %d\n", _mirror);

	_nColors = rootNode->getChild("nColors")->getIntegerContent();
	Log::getInstance().write("nColors: %d\n", _nColors);

	string palette = rootNode->getChild("palette")->getStringContent();
	uint8_t indexA = 0;
	uint8_t indexB = 0;
	for (int i = 0; i < _nColors; i++)
	{
		indexB = palette.find(' ', indexA);
		_palette.push_back(atoi(palette.substr(indexA, indexB).c_str()));
		indexA = indexB + 1;
	}
	Log::getInstance().write("palette: %s\n", palette.c_str());

	string table = rootNode->getChild("table")->getStringContent();
	indexA = 0;
	indexB = 0;
	for (int i = 0; i < N_LIMBS; i++)
	{
		indexB = table.find(' ', indexA);
		_table.push_back(atoi(table.substr(indexA, indexB).c_str()));
		indexA = indexB + 1;
	}
	Log::getInstance().write("table: %s\n", table.c_str());

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("anim", i++)) != NULL)
		_anims.push_back(new Anim(child));

	i = 0;
	while ((child = rootNode->getChild("command", i)) != NULL)
	{
		_commands.push_back(child->getIntegerContent());
		Log::getInstance().write("command: %d\n", _commands[i]);
		i++;
	}

	i = 0;
	while ((child = rootNode->getChild("frame", i)) != NULL)
	{
		_frames.push_back(new Frame(child, dirName + "frame_" + IO::getStringFromIndex(i, 3) + ".bmp"));
		i++;
	}

	Log::getInstance().unIndent();
}

Costume::~Costume()
{
	for (int i = 0; i < _anims.size(); i++)
		delete _anims[i];

	for (int i = 0; i < _frames.size(); i++)
		delete _frames[i];
};

