#include "Costume.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

map<string, Costume *> Costume::_instances;

Anim::Anim(string fileName, uint8_t id)
{
	Log::getInstance().write(LOG_INFO, "Anim\n");
	Log::getInstance().indent();

	int posB = fileName.find_last_of('/') - 1;
	int posA = fileName.find_last_of('.', posB) + 1;
	_name = fileName.substr(posA, posB + 1 - posA);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_id = id;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	XMLFile xmlFile;
	xmlFile.open(fileName);
	XMLNode *rootNode = xmlFile.getRootNode();

	_loop = rootNode->getChild("loop")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "loop: %s\n", _loop ? "true" : "false");

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("command", i)) != NULL)
	{
		_commands.push_back(child->getIntegerContent());
		i++;
	}

	Log::getInstance().unIndent();
}

Anim::~Anim()
{
}

Frame::Frame(XMLNode *node, string fileName)
{
	Log::getInstance().write(LOG_INFO, "Frame\n");
	Log::getInstance().indent();

	BMPFile bmpFile;
	bmpFile.open(fileName);
	Log::getInstance().write(LOG_INFO, "fileName: %s\n", fileName.c_str());

	_width = bmpFile.getWidth();
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);

	_height = bmpFile.getHeight();
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(bmpFile.getPixel(i, j));
		_pixels.push_back(pixelColumn);
	}

	_x = node->getChild("x")->getIntegerContent();
	_y = node->getChild("y")->getIntegerContent();
	_xInc = node->getChild("xInc")->getIntegerContent();
	_yInc = node->getChild("yInc")->getIntegerContent();

	Log::getInstance().unIndent();
}

Frame::~Frame()
{
}

Costume *Costume::getInstanceFromName(string costumeName)
{
	if (_instances.find(costumeName) == _instances.end())
		return NULL;
	return _instances[costumeName];
}

Costume::Costume(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Costume\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_instances[_name] = this;

	XMLFile xmlFile;
	xmlFile.open(dirName + "costume.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_id = _instances.size();
	Log::getInstance().write(LOG_INFO, "id: %d\n", _id);

	_mirror = rootNode->getChild("mirror")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "mirror: %d\n", _mirror);

	_nColors = rootNode->getChild("nColors")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "nColors: %d\n", _nColors);

	string palette = rootNode->getChild("palette")->getStringContent();
	uint8_t indexA = 0;
	uint8_t indexB = 0;
	for (int i = 0; i < _nColors; i++)
	{
		indexB = palette.find(' ', indexA);
		_palette.push_back(atoi(palette.substr(indexA, indexB).c_str()));
		indexA = indexB + 1;
	}

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("anim", i)) != NULL)
	{
		_anims.push_back(new Anim(dirName + "anims/" + child->getStringContent() + ".xml", i + 1));
		i++;
	}

	i = 0;
	while ((child = rootNode->getChild("frame", i)) != NULL)
	{
		_frames.push_back(new Frame(child, dirName + "frames/frame_" + IO::getStringFromIndex(i, 2) + ".bmp"));
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
}

