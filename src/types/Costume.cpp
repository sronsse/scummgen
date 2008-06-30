#include "Costume.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

vector<Anim *> Anim::_instances;
vector<Costume *> Costume::_instances;

Frame::Frame(XMLNode *node, string fileName)
{
	Log::getInstance().write("Frame\n");
	Log::getInstance().indent();

	BMPFile bmpFile(fileName);
	Log::getInstance().write("fileName: %s\n", fileName.c_str());

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

Anim *Anim::getInstanceFromName(string animName)
{
	for (int i = 0; i < _instances.size(); i++)
		if (_instances[i]->getName() == animName)
			return _instances[i];
	return NULL;
}

Anim::Anim(string dirName, uint8_t id)
{
	Log::getInstance().write("Anim\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	_id = id;
	Log::getInstance().write("id: %u\n", _id);

	XMLFile xmlFile(dirName + "anim.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_loop = rootNode->getChild("loop")->getBooleanContent();
	Log::getInstance().write("loop: %s\n", _loop ? "true" : "false");

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("command", i)) != NULL)
	{
		_commands.push_back(child->getIntegerContent());
		Log::getInstance().write("command: %d\n", _commands[i]);
		i++;
	}

	i = 0;
	while ((child = rootNode->getChild("frame", i)) != NULL)
	{
		_frames.push_back(new Frame(child, dirName + "frame_" + IO::getStringFromIndex(i, 2) + ".bmp"));
		i++;
	}

	Log::getInstance().unIndent();
}

Anim::~Anim()
{
	for (int i = 0; i < _frames.size(); i++)
		delete _frames[i];
}

Costume *Costume::getInstanceFromName(string costumeName)
{
	for (int i = 0; i < _instances.size(); i++)
		if (_instances[i]->getName() == costumeName)
			return _instances[i];
	return NULL;
}

Costume::Costume(string dirName)
{
	Log::getInstance().write("Costume\n");
	Log::getInstance().indent();

	_instances.push_back(this);

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	XMLFile xmlFile(dirName + "costume.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_id = _instances.size();
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

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("anim", i)) != NULL)
	{
		_anims.push_back(new Anim(dirName + child->getStringContent() + "/", i + 1));
		i++;
	}

	Log::getInstance().unIndent();
}

Costume::~Costume()
{
	for (int i = 0; i < _anims.size(); i++)
		delete _anims[i];
}

