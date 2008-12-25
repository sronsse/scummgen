#include "Costume.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Anim::N_DIRECTIONS = 4;

Anim::Anim(string fileName, uint8_t id)
{
	Log::getInstance().write(LOG_INFO, "Anim\n");
	Log::getInstance().indent();

	int posA = fileName.find_last_of('/') + 1;
	int posB = fileName.find_last_of('.') - 1;
	_name = fileName.substr(posA, posB - posA + 1);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_id = id;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	XMLFile xmlFile;
	xmlFile.open(fileName);
	XMLNode *rootNode = xmlFile.getRootNode();

	_loop = rootNode->getChild("loop")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "loop: %s\n", _loop ? "true" : "false");

	// Read the four sub animations
	readSubAnim(rootNode, "west");
	readSubAnim(rootNode, "east");
	readSubAnim(rootNode, "south");
	readSubAnim(rootNode, "north");

	Log::getInstance().unIndent();
}

void Anim::readSubAnim(XMLNode *rootNode, string name)
{
	vector<uint8_t> commands;
	int i = 0;
	XMLNode *child, *child2;
	if ((child = rootNode->getChild(name, 0)) != NULL)
		while ((child2 = child->getChild("command", i++)) != NULL)
			commands.push_back(child2->getIntegerContent());
	else
		commands.push_back(0); // When no frame is set for a certain direction, we just set the first frame by default
	_commands.push_back(commands);
}

Anim::~Anim()
{
}

Frame::Frame(XMLNode *node, string dirName)
{
	Log::getInstance().write(LOG_INFO, "Frame\n");
	Log::getInstance().indent();

	_bitmapName = node->getChild("bitmapName")->getStringContent();
	uint16_t x = node->getChild("x")->getIntegerContent();
	uint16_t y = node->getChild("y")->getIntegerContent();
	_width = node->getChild("width")->getIntegerContent();
	_height = node->getChild("height")->getIntegerContent();
	_xOffset = node->getChild("xOffset")->getIntegerContent();
	_yOffset = node->getChild("yOffset")->getIntegerContent();

	Log::getInstance().write(LOG_INFO, "bitmapName: %s\n", _bitmapName.c_str());
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	BMPFile bmpFile;
	bmpFile.open(dirName + _bitmapName + ".bmp");
	for (int i = 0; i < _width; i++)
	{
		vector<uint8_t> pixelColumn;
		for (int j = 0; j < _height; j++)
			pixelColumn.push_back(bmpFile.getPixel(x + i, y + j));
		_pixels.push_back(pixelColumn);
	}

	Log::getInstance().unIndent();
}

Frame::~Frame()
{
}

Costume::Costume(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Costume\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB - posA + 1);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	XMLFile xmlFile;
	xmlFile.open(dirName + "costume.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	static uint16_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %d\n", _id);

	_width = rootNode->getChild("width")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "width: %d\n", _width);

	_height = rootNode->getChild("height")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "height: %d\n", _height);

	_mirror = rootNode->getChild("mirror")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "mirror: %d\n", _mirror);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("anim", i)) != NULL)
		_anims.push_back(new Anim(dirName + "anims/" + child->getStringContent() + ".xml", i++));

	i = 0;
	while ((child = rootNode->getChild("frame", i++)) != NULL)
		_frames.push_back(new Frame(child, dirName + "frames/"));

	// Check for empty lists
	if (_anims.empty())
		Log::getInstance().write(LOG_ERROR, "Costume doesn't have any animation !\n");
	if (_frames.empty())
		Log::getInstance().write(LOG_ERROR, "Costume doesn't have any frame !\n");

	// Get the costume colors from the first frame
	_paletteBaseIndex = 0;
	BMPFile bmpFile;
	bmpFile.open(dirName + "frames/" + _frames[0]->getBitmapName() + ".bmp");
	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		_colors.push_back(bmpFile.getColor(i));

	Log::getInstance().unIndent();
}

Costume::~Costume()
{
	for (int i = 0; i < _anims.size(); i++)
		delete _anims[i];
	for (int i = 0; i < _frames.size(); i++)
		delete _frames[i];
}
