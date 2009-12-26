#include "Costume.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Palette.hpp"

const uint8_t Anim::N_DIRECTIONS = 4;
const string Costume::XML_FILE_NAME = "costume.xml";

Anim::Anim():
_id(0),
_name(""),
_loop(false)
{
	_commands.resize(N_DIRECTIONS);
}

void Anim::loadSubAnim(XMLNode *node, AnimDirection direction)
{
	string name;
	switch (direction)
	{
		case ANIM_WEST:
			name = "west";
			break;
		case ANIM_EAST:
			name = "east";
			break;
		case ANIM_SOUTH:
			name = "south";
			break;
		case ANIM_NORTH:
			name = "north";
	}

	int i = 0;
	XMLNode *child, *child2;
	if ((child = node->getChild(name, 0)) != NULL)
		while ((child2 = child->getChild("command", i++)) != NULL)
			_commands[direction].push_back(child2->getIntegerContent());
	else
		_commands[direction].push_back(0); // When no command is present, we set the first frame by default
}

void Anim::saveSubAnim(XMLNode *node, AnimDirection direction)
{
	string name;
	switch (direction)
	{
		case ANIM_WEST:
			name = "west";
			break;
		case ANIM_EAST:
			name = "east";
			break;
		case ANIM_SOUTH:
			name = "south";
			break;
		case ANIM_NORTH:
			name = "north";
	}

	// Write commands only if there are multiple entries, or a single entry which is different than 0
	// as we're always reading this by default when no command is present in the XML file
	if (_commands[direction].size() > 1 || _commands[direction][0] != 0)
	{
		XMLNode *child = new XMLNode(name);
		node->addChild(child);
		for (int i = 0; i < _commands[direction].size(); i++)
		{
			XMLNode *child2 = new XMLNode("command", _commands[direction][i]);
			child->addChild(child2);
		}
	}
}

void Anim::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Anim\n");
	Log::indent();

	_name = node->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_loop = node->getChild("loop")->getBooleanContent();
	Log::write(LOG_INFO, "loop: %s\n", _loop ? "true" : "false");

	// Load the four sub animations
	loadSubAnim(node, ANIM_WEST);
	loadSubAnim(node, ANIM_EAST);
	loadSubAnim(node, ANIM_SOUTH);
	loadSubAnim(node, ANIM_NORTH);

	Log::unIndent();
}

void Anim::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Anim\n");
	Log::indent();

	node->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	node->addChild(new XMLNode("loop", _loop));
	Log::write(LOG_INFO, "loop: %s\n", _loop ? "true" : "false");

	// Save the four sub animations
	saveSubAnim(node, ANIM_WEST);
	saveSubAnim(node, ANIM_EAST);
	saveSubAnim(node, ANIM_SOUTH);
	saveSubAnim(node, ANIM_NORTH);

	Log::unIndent();
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
	Log::write(LOG_INFO, "Frame\n");
	Log::indent();

	_bitmapPath = dirPath + node->getChild("bitmapName")->getStringContent();
	Log::write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	_x = node->getChild("x")->getIntegerContent();
	Log::write(LOG_INFO, "x: %u\n", _x);

	_y = node->getChild("y")->getIntegerContent();
	Log::write(LOG_INFO, "y: %u\n", _y);

	_width = node->getChild("width")->getIntegerContent();
	Log::write(LOG_INFO, "width: %u\n", _width);

	_height = node->getChild("height")->getIntegerContent();
	Log::write(LOG_INFO, "height: %u\n", _height);

	_xOffset = node->getChild("xOffset")->getIntegerContent();
	Log::write(LOG_INFO, "xOffset: %d\n", _xOffset);

	_yOffset = node->getChild("yOffset")->getIntegerContent();
	Log::write(LOG_INFO, "yOffset: %d\n", _yOffset);

	Log::unIndent();
}

void Frame::save(XMLNode *node, string dirPath)
{
	Log::write(LOG_INFO, "Frame\n");
	Log::indent();

	string bitmapName = _bitmapPath.substr(_bitmapPath.find_last_of('/') + 1);
	node->addChild(new XMLNode("bitmapName", bitmapName));
	string newBitmapPath = dirPath + bitmapName;
	if (_bitmapPath != newBitmapPath)
	{
		if (!IO::copyFile(_bitmapPath, newBitmapPath))
			Log::write(LOG_ERROR, "Could not copy file \"%s\" to \"%s\" !\n", _bitmapPath.c_str(), newBitmapPath.c_str());
		_bitmapPath = newBitmapPath;
	}
	Log::write(LOG_INFO, "bitmapPath: %s\n", _bitmapPath.c_str());

	node->addChild(new XMLNode("x", _x));
	Log::write(LOG_INFO, "x: %u\n", _x);

	node->addChild(new XMLNode("y", _y));
	Log::write(LOG_INFO, "y: %u\n", _y);

	node->addChild(new XMLNode("width", _width));
	Log::write(LOG_INFO, "width: %u\n", _width);

	node->addChild(new XMLNode("height", _height));
	Log::write(LOG_INFO, "height: %u\n", _height);

	node->addChild(new XMLNode("xOffset", _xOffset));
	Log::write(LOG_INFO, "xOffset: %d\n", _xOffset);

	node->addChild(new XMLNode("yOffset", _yOffset));
	Log::write(LOG_INFO, "yOffset: %d\n", _yOffset);

	Log::unIndent();
}

void Frame::prepare(Palette *palette, PaletteData *paletteData, vector<uint8_t> &redirectionPalette)
{
	if (_width == 0 || _height == 0)
		Log::write(LOG_ERROR, "Frame dimensions can't be equal to 0 !\n");

	// Open original bitmap
	BMPFile bmpFile;
	bmpFile.open(_bitmapPath);

	// Get original palette from bitmap
	vector<Color> colors;
	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		colors.push_back(bmpFile.getColor(i));

	// Clear any existing pixels
	_pixels.clear();

	// Get pixels from bitmap
	for (int x = 0; x < _width; x++)
	{
		vector<uint8_t> pixelColumn;
		for (int y = 0; y < _height; y++)
			pixelColumn.push_back(bmpFile.getPixel(_x + x, _y + y));
		_pixels.push_back(pixelColumn);
	}

	// Add colors to palette (and update pixels)
	palette->add(&colors, _pixels, paletteData);

	// Modify pixels and update redirection palette
	for (int x = 0; x < _width; x++)
		for (int y = 0; y < _height; y++)
		{
			bool found = false;
			for (int i = 0; i < redirectionPalette.size(); i++)
				if (_pixels[x][y] == redirectionPalette[i])
				{
					_pixels[x][y] = i;
					found = true;
					break;
				}
			if (!found)
			{
				redirectionPalette.push_back(_pixels[x][y]);
				_pixels[x][y] = redirectionPalette.size() - 1;
			}
		}

}

Frame::~Frame()
{
}

Costume::Costume():
_id(0),
_name(""),
_mirror(true),
_width(0),
_height(0),
_paletteData(NULL)
{
}

void Costume::load(string dirPath)
{
	Log::write(LOG_INFO, "Costume\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_mirror = rootNode->getChild("mirror")->getBooleanContent();
	Log::write(LOG_INFO, "mirror: %d\n", _mirror);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("anim", i++)) != NULL)
	{
		Anim *anim = new Anim();
		anim->load(child);
		_anims.push_back(anim);
	}

	i = 0;
	while ((child = rootNode->getChild("frame", i++)) != NULL)
	{
		Frame *frame = new Frame();
		frame->load(child, dirPath);
		_frames.push_back(frame);
	}

	_paletteData = new PaletteData();
	_paletteData->load(dirPath);

	Log::unIndent();
}

void Costume::save(string dirPath)
{
	Log::write(LOG_INFO, "Costume\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("costume");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	rootNode->addChild(new XMLNode("mirror", _mirror));
	Log::write(LOG_INFO, "mirror: %d\n", _mirror);

	for (int i = 0; i < _anims.size(); i++)
	{
		XMLNode *child = new XMLNode("anim");
		rootNode->addChild(child);
		_anims[i]->save(child);
	}

	for (int i = 0; i < _frames.size(); i++)
	{
		XMLNode *child = new XMLNode("frame");
		rootNode->addChild(child);
		_frames[i]->save(child, dirPath);
	}

	_paletteData->save(dirPath);

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save costume to the specified directory !\n");

	Log::unIndent();
}

void Costume::prepare(Palette *palette)
{
	Log::write(LOG_INFO, "Preparing costume \"%s\"...\n", _name.c_str());
	Log::indent();

	if (_anims.empty())
		Log::write(LOG_ERROR, "Costume doesn't have any animation !\n");
	if (_frames.empty())
		Log::write(LOG_ERROR, "Costume doesn't have any frame !\n");

	// Prepare frames
	for (int i = 0; i < _frames.size(); i++)
		_frames[i]->prepare(palette, _paletteData, _redirectionPalette);

	// Set animation IDs
	for (int i = 0; i < _anims.size(); i++)
		_anims[i]->setID(i);

	// Set dimensions
	_width = 0;
	_height = 0;
	for (int i = 0; i < _frames.size(); i++)
	{
		if (_width < _frames[i]->getWidth())
			_width = _frames[i]->getWidth();
		if (_height < _frames[i]->getHeight())
			_height = _frames[i]->getHeight();
	}

	Log::write(LOG_INFO, "Palette cursor: %u...\n", palette->getCursor());
	Log::unIndent();
}

Costume::~Costume()
{
	for (int i = 0; i < _anims.size(); i++)
		delete _anims[i];
	for (int i = 0; i < _frames.size(); i++)
		delete _frames[i];
	if (_paletteData != NULL)
		delete _paletteData;
}
