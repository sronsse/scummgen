#include "Palette.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint16_t Palette::MAX_COLORS = 256;

Cycle::Cycle(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Cycle\n");
	Log::getInstance().indent();

	_id = node->getChild("id")->getIntegerContent();
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

Palette::Palette(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Palette\n");
	Log::getInstance().indent();

	BMPFile bmpFile;
	bmpFile.open(dirName +  "background.bmp");

	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		_colors.push_back(bmpFile.getColor(i));

	Color black = { 0, 0, 0 };
	for (int i = _colors.size(); i < MAX_COLORS; i++)
		_colors.push_back(black);

	XMLFile xmlFile;
	xmlFile.open(dirName + "palette.xml");
	XMLNode *node = xmlFile.getRootNode();

	_transparentIndex = node->getChild("transparentIndex")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "transparentIndex: %u\n", _transparentIndex);

	XMLNode *childNode;
	for (int i = 0; (childNode = node->getChild("cycle", i)) != NULL; i++)
		_cycles.push_back(new Cycle(childNode));

	Log::getInstance().unIndent();
}

Palette::~Palette()
{
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles[i];
}

