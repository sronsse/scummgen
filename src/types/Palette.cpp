#include "Palette.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

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

	static uint8_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

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
}

void Palette::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Palette\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "palette.xml");
	XMLNode *node = xmlFile.getRootNode();

	_transparentIndex = node->getChild("transparentIndex")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "transparentIndex: %u\n", _transparentIndex);

	_colors.resize(MAX_COLORS);
	_startCursor = 0;
	_endCursor = MAX_COLORS;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("cycle", i++)) != NULL)
	{
		Cycle *cycle = new Cycle();
		cycle->load(child);
		_cycles.push_back(cycle);
	}

	Log::getInstance().unIndent();
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
