#include "Cycle.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Cycle::Cycle():
_id(0),
_name(),
_start(0),
_end(0),
_delay(0),
_forward(true)
{
}

void Cycle::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Cycle\n");
	Log::indent();

	_name = node->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_start = node->getChild("start")->getIntegerContent();
	Log::write(LOG_INFO, "start: %u\n", _start);

	_end = node->getChild("end")->getIntegerContent();
	Log::write(LOG_INFO, "end: %u\n", _end);

	_delay = node->getChild("delay")->getIntegerContent();
	Log::write(LOG_INFO, "delay: %u\n", _delay);

	_forward = node->getChild("forward")->getBooleanContent();
	Log::write(LOG_INFO, "forward: %s\n", _forward ? "true" : "false");

	Log::unIndent();
}

void Cycle::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Cycle\n");
	Log::indent();

	node->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	node->addChild(new XMLNode("start", _start));
	Log::write(LOG_INFO, "start: %u\n", _start);

	node->addChild(new XMLNode("end", _end));
	Log::write(LOG_INFO, "end: %u\n", _end);

	node->addChild(new XMLNode("delay", _delay));
	Log::write(LOG_INFO, "delay: %u\n", _delay);

	node->addChild(new XMLNode("forward", _forward));
	Log::write(LOG_INFO, "forward: %s\n", _forward ? "true" : "false");

	Log::unIndent();
}

Cycle::~Cycle()
{
}
