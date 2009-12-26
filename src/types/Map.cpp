#include "Map.hpp"
#include <algorithm>
#include <map>
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

const string Map::XML_FILE_NAME = "map.xml";
const uint8_t Map::N_SLOTS = 4;

Box::Box():
_id(0),
_name(""),
_ulx(0),
_uly(0),
_urx(0),
_ury(0),
_lrx(0),
_lry(0),
_llx(0),
_lly(0),
_mask(0),
_flags(0),
_scale(0)
{
}

void Box::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Box\n");
	Log::indent();

	_name = node->getChild("name")->getStringContent();
	_ulx = node->getChild("ulx")->getIntegerContent();
	_uly = node->getChild("uly")->getIntegerContent();
	_urx = node->getChild("urx")->getIntegerContent();
	_ury = node->getChild("ury")->getIntegerContent();
	_lrx = node->getChild("lrx")->getIntegerContent();
	_lry = node->getChild("lry")->getIntegerContent();
	_llx = node->getChild("llx")->getIntegerContent();
	_lly = node->getChild("lly")->getIntegerContent();
	_mask = node->getChild("mask")->getIntegerContent();
	_flags = node->getChild("flags")->getIntegerContent();
	_scale = node->getChild("scale")->getIntegerContent();

	Log::unIndent();
}

void Box::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Box\n");
	Log::indent();

	node->addChild(new XMLNode("name", _name));
	node->addChild(new XMLNode("ulx", _ulx));
	node->addChild(new XMLNode("uly", _uly));
	node->addChild(new XMLNode("urx", _urx));
	node->addChild(new XMLNode("ury", _ury));
	node->addChild(new XMLNode("lrx", _lrx));
	node->addChild(new XMLNode("lry", _lry));
	node->addChild(new XMLNode("llx", _llx));
	node->addChild(new XMLNode("lly", _lly));
	node->addChild(new XMLNode("mask", _mask));
	node->addChild(new XMLNode("flags", _flags));
	node->addChild(new XMLNode("scale", _scale));

	Log::unIndent();
}

Box::~Box()
{
}

Scale::Scale():
_s1(0),
_y1(0),
_s2(0),
_y2(0)
{
}

void Scale::load(XMLNode *node)
{
	Log::write(LOG_INFO, "Scale\n");
	Log::indent();

	_s1 = node->getChild("s1")->getIntegerContent();
	_y1 = node->getChild("y1")->getIntegerContent();
	_s2 = node->getChild("s2")->getIntegerContent();
	_y2 = node->getChild("y2")->getIntegerContent();

	Log::unIndent();
}

void Scale::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Scale\n");
	Log::indent();

	node->addChild(new XMLNode("s1", _s1));
	node->addChild(new XMLNode("y1", _y1));
	node->addChild(new XMLNode("s2", _s2));
	node->addChild(new XMLNode("y2", _y2));

	Log::unIndent();
}

Scale::~Scale()
{
}

Map::Map()
{
}

void Map::load(string dirPath)
{
	Log::write(LOG_INFO, "Map\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("box", i++)) != NULL)
	{
		Box *box = new Box();
		box->load(child);
		_boxes.push_back(box);
	}

	i = 0;
	while ((child = rootNode->getChild("scale", i++)) != NULL)
	{
		Scale *scale = new Scale();
		scale->load(child);
		_scales.push_back(scale);
	}
	for (i = _scales.size(); i < N_SLOTS; i++)
		_scales.push_back(new Scale());

	Log::unIndent();
}

void Map::save(string dirPath)
{
	Log::write(LOG_INFO, "Map\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("map");
	xmlFile.setRootNode(rootNode);

	for (int i = 0; i < _boxes.size(); i++)
	{
		XMLNode *child = new XMLNode("box");
		rootNode->addChild(child);
		_boxes[i]->save(child);
	}

	for (int i = 0; i < _scales.size(); i++)
	{
		XMLNode *child = new XMLNode("scale");
		rootNode->addChild(child);
		_scales[i]->save(child);
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save map to the specified directory !\n");

	Log::unIndent();
}

void Map::prepare()
{
	Log::write(LOG_INFO, "Preparing map...\n");
	Log::indent();

	// Set boxes IDs
	for (int i = 0; i < _boxes.size(); i++)
		_boxes[i]->setID(i + 1);

	Log::unIndent();
}

Map::~Map()
{
	for (int i = 0; i < _boxes.size(); i++)
		delete _boxes[i];

	for (int i = 0; i < _scales.size(); i++)
		delete _scales[i];
}
