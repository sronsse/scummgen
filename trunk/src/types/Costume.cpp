#include "Costume.hpp"
#include "util/BMPFile.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Limb::MODE_SINGLE_FRAME = 1;
const uint8_t Limb::MODE_STOP_LIMB = 4;
const uint8_t Limb::MODE_START_LIMB = 5;
const uint8_t Costume::N_DIRECTIONS = 4;
const uint8_t Costume::N_CHANNELS = 3;
const uint8_t Costume::BOMP_CODEC = 5;

Limb::Limb(XMLNode *node)
{
	Log::getInstance().write("Limb\n");
	Log::getInstance().indent();

	_mode = node->getChild("mode")->getIntegerContent();
	Log::getInstance().write("mode: %u\n", _mode);

	if (_mode != MODE_SINGLE_FRAME && _mode != MODE_STOP_LIMB && _mode != MODE_START_LIMB)
	{
		_start = node->getChild("start")->getIntegerContent();
		Log::getInstance().write("start: %u\n", _start);

		_length = node->getChild("length")->getIntegerContent();
		Log::getInstance().write("length: %u\n", _length);
	}

	Log::getInstance().unIndent();
}

Limb::~Limb()
{
}

Anim::Anim(XMLNode *node)
{
	Log::getInstance().write("Anim\n");
	Log::getInstance().indent();

	_mask = node->getChild("mask")->getIntegerContent();
	Log::getInstance().write("mask: %04x\n", _mask);

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

Frame::Frame(string fileName):
_pixels(NULL)
{
	BMPFile bmpFile(fileName);
	_width = bmpFile.getWidth();
	_height = bmpFile.getHeight();
	_pixels = new uint8_t *[_width];
	for (int i = 0; i < _width; i++)
		_pixels[i] = new uint8_t[_height];
	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _height; j++)
			_pixels[i][j] = bmpFile.getPixel(i, j);
}

Frame::~Frame()
{
	if (_pixels != NULL)
	{
		for (int i = 0; i < _width; i++)
			delete [] _pixels[i];
		delete [] _pixels;
	}
}

Costume::Costume(string dirName)
{
	Log::getInstance().write("Costume\n");
	Log::getInstance().indent();

	XMLFile xmlFile(dirName + "costume.xml");
	XMLNode *node = xmlFile.getRootNode();

	// id
	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %u\n", _id);

	// mirror
	_mirror = node->getChild("mirror")->getBooleanContent();
	Log::getInstance().write("mirror: %u\n", _mirror);

	// palette
	BMPFile bmpFile(dirName + "frame_000.bmp");
	Log::getInstance().write("nColors: %u\n", bmpFile.getNumberOfColors());
	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		for (int j = 0; j < N_CHANNELS; j++)
			_palette.push_back(bmpFile.getColor(i, j));

	// frames
	uint32_t nFrames = node->getChild("nFrames")->getIntegerContent();
	Log::getInstance().write("nFrames: %u\n", nFrames);
	for (int i = 0; i < nFrames; i++)
		_frames.push_back(new Frame(dirName + "frame_" + IO::getStringFromIndex(i, 3) + ".bmp"));

	// commands
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("command", i++)) != NULL)
		_commands.push_back(child->getIntegerContent());
	Log::getInstance().write("nCommands: %u\n", _commands.size());

	// anims
	i = 0;
	while ((child = node->getChild("anim", i++)) != NULL)
		_anims.push_back(new Anim(child));

	Log::getInstance().unIndent();
};

Costume::~Costume()
{
	for (int i = 0; i < _frames.size(); i++)
		delete _frames[i];

	for (int i = 0; i < _anims.size(); i++)
		delete _anims[i];
};

