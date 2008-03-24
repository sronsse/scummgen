#include "Palette.hpp"
#include "util/BMPFile.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const uint8_t Palette::N_CHANNELS = 3;

Cycle::Cycle(XMLNode *node)
{
	Log::getInstance().write("Cycle\n");
	Log::getInstance().indent();

	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %u\n", _id);

	_start = node->getChild("start")->getIntegerContent();
	Log::getInstance().write("start: %u\n", _start);

	_end = node->getChild("end")->getIntegerContent();
	Log::getInstance().write("end: %u\n", _end);

	_delay = node->getChild("delay")->getIntegerContent();
	Log::getInstance().write("delay: %u\n", _delay);

	_forward = node->getChild("forward")->getBooleanContent();
	Log::getInstance().write("forward: %s\n", _forward ? "true" : "false");

	Log::getInstance().unIndent();
}

Cycle::~Cycle()
{
}

Palette::Palette(string dirName)
{
	Log::getInstance().write("Palette\n");
	Log::getInstance().indent();

	BMPFile bmpFile(dirName +  "background.bmp");

	for (int i = 0; i < bmpFile.getNumberOfColors(); i++)
		for (int j = 0; j < 3; j++)
			_colors.push_back(bmpFile.getColor(i, j));

	XMLFile xmlFile(dirName + "palette.xml");
	XMLNode *node = xmlFile.getRootNode();

	_transparentIndex = node->getChild("transparentIndex")->getIntegerContent();
	Log::getInstance().write("transparentIndex: %u\n", _transparentIndex);

	XMLNode *childNode;
	for (int i = 0; (childNode = node->getChild("cycle", i)) != NULL; i++)
		_cycles.push_back(new Cycle(childNode));

	Log::getInstance().unIndent();
}

Palette::~Palette()
{
	for (int i = 0; i < _cycles.size(); i++)
		delete _cycles.at(i);
}

