#include "Palette.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

// Default palette colors (names obtained from http://chir.ag/projects/name-that-color/)
const Color Palette::COLOR_BLACK = { 0, 0, 0 };
const Color Palette::COLOR_DARK_BLUE = { 0, 0, 171 };
const Color Palette::COLOR_JAPANESE_LAUREL = { 0, 171, 0 };
const Color Palette::COLOR_PERSIAN_GREEN = { 0, 171, 171 };
const Color Palette::COLOR_BRIGHT_RED = { 171, 0, 0 };
const Color Palette::COLOR_FLIRT = { 171, 0, 171 };
const Color Palette::COLOR_CHELSEA_GEM = { 171, 87, 0 };
const Color Palette::COLOR_SILVER_CHALICE = { 171, 171, 171 };
const Color Palette::COLOR_SCORPION = { 87, 87, 87 };
const Color Palette::COLOR_DODGER_BLUE = { 87, 87, 255 };
const Color Palette::COLOR_SCREAMIN_GREEN = { 87, 255, 87 };
const Color Palette::COLOR_AQUAMARINE = { 87, 255, 255 };
const Color Palette::COLOR_PERSIMMON = { 255, 87, 87 };
const Color Palette::COLOR_PINK_FLAMINGO = { 255, 87, 255 };
const Color Palette::COLOR_GORSE = { 255, 255, 87 };
const Color Palette::COLOR_WHITE = { 255, 255, 255 };

const uint16_t Palette::MAX_COLORS = 256;

Cycle::Cycle():
_id(0),
_start(0),
_end(0),
_delay(0),
_forward(true)
{}

void Cycle::load(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Cycle\n");
	Log::getInstance().indent();

	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_start = node->getChild("start")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "start: %u\n", _start);

	_end = node->getChild("end")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "end: %u\n", _end);

	_delay = node->getChild("delay")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "delay: %u\n", _delay);

	_forward = node->getChild("forward")->getBooleanContent();
	Log::getInstance().write(LOG_INFO, "forward: %s\n", _forward ? "true" : "false");

	Log::getInstance().unIndent();
}

Cycle::~Cycle()
{
}

Palette::Palette():
_transparentIndex(0)
{
	// Set palette size and default colors
	_colors.push_back(COLOR_BLACK);
	_colors.push_back(COLOR_DARK_BLUE);
	_colors.push_back(COLOR_JAPANESE_LAUREL);
	_colors.push_back(COLOR_PERSIAN_GREEN);
	_colors.push_back(COLOR_BRIGHT_RED);
	_colors.push_back(COLOR_FLIRT);
	_colors.push_back(COLOR_CHELSEA_GEM);
	_colors.push_back(COLOR_SILVER_CHALICE);
	_colors.push_back(COLOR_SCORPION);
	_colors.push_back(COLOR_DODGER_BLUE);
	_colors.push_back(COLOR_SCREAMIN_GREEN);
	_colors.push_back(COLOR_AQUAMARINE);
	_colors.push_back(COLOR_PERSIMMON);
	_colors.push_back(COLOR_PINK_FLAMINGO);
	_colors.push_back(COLOR_GORSE);
	_colors.push_back(COLOR_WHITE);
	_colors.resize(MAX_COLORS);
	_startCursor = 16;
	_endCursor = MAX_COLORS;
}

void Palette::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Palette\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "palette.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_transparentIndex = rootNode->getChild("transparentIndex")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "transparentIndex: %u\n", _transparentIndex);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("cycle", i++)) != NULL)
	{
		Cycle *cycle = new Cycle();
		cycle->load(child);
		_cycles.push_back(cycle);
	}

	Log::getInstance().unIndent();
}

void Palette::prepare()
{
	// Set cycles IDs
	for (int i = 0; i < _cycles.size(); i++)
		_cycles[i]->setID(i + 1);
}

uint8_t Palette::add(string bitmapPath, bool fromStart)
{
	BMPFile bmpFile;
	bmpFile.open(bitmapPath);

	if (fromStart)
	{
		for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		{
			_colors[_startCursor++] = bmpFile.getColor(i);
			if (_startCursor == _endCursor)
				Log::getInstance().write(LOG_ERROR, "Palette contains too many colors !\n");
		}
		return _startCursor - bmpFile.getNumberOfColors();
	}
	else
	{
		for (int i = bmpFile.getNumberOfColors() - 1; i >= 0; i--)
		{
			_colors[--_endCursor] = bmpFile.getColor(i);
			if (_startCursor == _endCursor)
				Log::getInstance().write(LOG_ERROR, "Palette contains too many colors !\n");
		}
		return _endCursor;
	}
}

Palette::~Palette()
{
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles[i];
}
