#include "Map.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Matrix::Matrix(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Matrix\n");
	Log::getInstance().indent();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("entry", i++)) != NULL)
	{
		_boxAs.push_back(child->getChild("boxA")->getIntegerContent());
		_boxBs.push_back(child->getChild("boxB")->getIntegerContent());
		_dests.push_back(child->getChild("dest")->getIntegerContent());
	}

	Log::getInstance().unIndent();
}

Matrix::~Matrix()
{
}

Box::Box(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Box\n");
	Log::getInstance().indent();

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
	_scaleSlot = node->getChild("scaleSlot")->getIntegerContent();
	_scale = node->getChild("scale")->getIntegerContent();
	_matrix = new Matrix(node->getChild("matrix"));

	Log::getInstance().unIndent();
}

Box::~Box()
{
	delete _matrix;
}

Scale::Scale(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Scale\n");
	Log::getInstance().indent();

	_s1 = node->getChild("s1")->getIntegerContent();
	_y1 = node->getChild("y1")->getIntegerContent();
	_s2 = node->getChild("s2")->getIntegerContent();
	_y2 = node->getChild("y2")->getIntegerContent();

	Log::getInstance().unIndent();
}

Scale::~Scale()
{
}

Map::Map(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Map\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirName + "map.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	if (rootNode != NULL)
	{
		int i = 0;
		XMLNode *child;
		while ((child = rootNode->getChild("box", i++)) != NULL)
			_boxes.push_back(new Box(child));

		i = 0;
		while ((child = rootNode->getChild("scale", i++)) != NULL)
			_scales.push_back(new Scale(child));
	}
	else
		Log::getInstance().write(LOG_WARNING, "Room doesn't contain any map !\n");

	Log::getInstance().unIndent();
}

Map::~Map()
{
	for (int i = 0; i < _boxes.size(); i++)
		delete _boxes[i];

	for (int i = 0; i < _scales.size(); i++)
		delete _scales[i];
}

