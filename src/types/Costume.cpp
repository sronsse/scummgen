#include "Costume.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Anim::N_DIRECTIONS = 4;

Anim::Anim():
_id(0),
_name(""),
_loop(false)
{
}

void Anim::load(XMLNode *node, uint8_t id)
{
	Log::getInstance().write(LOG_INFO, "Anim\n");
	Log::getInstance().indent();

	_id = id;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_loop = node->getChild("loop")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "loop: %s\n", _loop ? "true" : "false");

	// Read the four sub animations
	readSubAnim(node, "west");
	readSubAnim(node, "east");
	readSubAnim(node, "south");
	readSubAnim(node, "north");

	Log::getInstance().unIndent();
}

void Anim::readSubAnim(XMLNode *node, string name)
{
	vector<uint8_t> commands;
	int i = 0;
	XMLNode *child, *child2;
	if ((child = node->getChild(name, 0)) != NULL)
		while ((child2 = child->getChild("command", i++)) != NULL)
			commands.push_back(child2->getIntegerContent());
	else
		commands.push_back(0); // When no frame is set for a certain direction, we just set the first frame by default
	_commands.push_back(commands);
}

Anim::~Anim()
{
}

Frame::Frame():
_bitmapPath(""),
_x(0),
_y(0),
_width(0),
_height(0),
_xOffset(0),
_yOffset(0)
{
}

void Frame::load(XMLNode *node, string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Frame\n");
	Log::getInstance().indent();

	_bitmapPath = dirPath + node->getChild("bitmapName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	_x = node->getChild("x")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "x: %u\n", _x);

	_y = node->getChild("y")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "y: %u\n", _y);

	_width = node->getChild("width")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);

	_height = node->getChild("height")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	_xOffset = node->getChild("xOffset")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "xOffset: %d\n", _xOffset);

	_yOffset = node->getChild("yOffset")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "yOffset: %d\n", _yOffset);

	if (_width == 0 || _height == 0)
		Log::getInstance().write(LOG_ERROR, "Frame dimensions can't be equal to 0 !\n");

	Log::getInstance().unIndent();
}

Frame::~Frame()
{
}

Costume::Costume():
_id(0),
_name(""),
_mirror(true),
_width(0),
_height(0)
{
}

void Costume::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Costume\n");
	Log::getInstance().indent();

	static uint16_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %d\n", _id);

	XMLFile xmlFile;
	xmlFile.open(dirPath + "costume.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_mirror = rootNode->getChild("mirror")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "mirror: %d\n", _mirror);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("anim", i)) != NULL)
	{
		Anim *anim = new Anim();
		anim->load(child, i++);
		_anims.push_back(anim);
	}

	i = 0;
	while ((child = rootNode->getChild("frame", i++)) != NULL)
	{
		Frame *frame = new Frame();
		frame->load(child, dirPath);
		_frames.push_back(frame);
	}

	if (_anims.empty())
		Log::getInstance().write(LOG_ERROR, "Costume doesn't have any animation !\n");
	if (_frames.empty())
		Log::getInstance().write(LOG_ERROR, "Costume doesn't have any frame !\n");

	_width = 0;
	_height = 0;
	for (int i = 0; i < _frames.size(); i++)
	{
		if (_width < _frames[i]->getWidth())
			_width = _frames[i]->getWidth();
		if (_height < _frames[i]->getHeight())
			_height = _frames[i]->getHeight();
	}
	Log::getInstance().write(LOG_INFO, "width: %d\n", _width);
	Log::getInstance().write(LOG_INFO, "height: %d\n", _height);

	Log::getInstance().unIndent();
}

Costume::~Costume()
{
	for (int i = 0; i < _anims.size(); i++)
		delete _anims[i];
	for (int i = 0; i < _frames.size(); i++)
		delete _frames[i];
}
