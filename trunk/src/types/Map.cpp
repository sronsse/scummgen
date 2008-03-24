#include "Map.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"

Matrix::Matrix(XMLNode *node)
{
	Log::getInstance().write("Matrix\n");
	Log::getInstance().indent();

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("entry", i++)) != NULL)
	{
		_boxAs.push_back(child->getChild("boxA")->getIntegerContent());
		Log::getInstance().write("boxA: %u\n", _boxAs[_boxAs.size() - 1]);

		_boxBs.push_back(child->getChild("boxB")->getIntegerContent());
		Log::getInstance().write("boxB: %u\n", _boxBs[_boxBs.size() - 1]);

		_dests.push_back(child->getChild("dest")->getIntegerContent());
		Log::getInstance().write("dest: %u\n", _dests[_dests.size() - 1]);
	}

	Log::getInstance().unIndent();
}

Matrix::~Matrix()
{
}

Box::Box(XMLNode *node)
{
	Log::getInstance().write("Box\n");
	Log::getInstance().indent();

	_ulx = node->getChild("ulx")->getIntegerContent();
	_uly = node->getChild("uly")->getIntegerContent();
	Log::getInstance().write("ul: (%d, %d)\n", _ulx, _uly);

	_urx = node->getChild("urx")->getIntegerContent();
	_ury = node->getChild("ury")->getIntegerContent();
	Log::getInstance().write("ur: (%d, %d)\n", _urx, _ury);

	_lrx = node->getChild("lrx")->getIntegerContent();
	_lry = node->getChild("lry")->getIntegerContent();
	Log::getInstance().write("lr: (%d, %d)\n", _lrx, _lry);

	_llx = node->getChild("llx")->getIntegerContent();
	_lly = node->getChild("lly")->getIntegerContent();
	Log::getInstance().write("ll: (%d, %d)\n", _llx, _lly);

	_mask = node->getChild("mask")->getIntegerContent();
	Log::getInstance().write("mask: %08x\n", _mask);

	_flags = node->getChild("flags")->getIntegerContent();
	Log::getInstance().write("flags: %08x\n", _flags);

	_scaleSlot = node->getChild("scaleSlot")->getIntegerContent();
	Log::getInstance().write("scaleSlot: %u\n", _scaleSlot);

	_scale = node->getChild("scale")->getIntegerContent();
	Log::getInstance().write("scale: %u\n", _scale);

	_matrix = new Matrix(node->getChild("matrix"));

	Log::getInstance().unIndent();
}

Box::~Box()
{
	delete _matrix;
}

Scale::Scale(XMLNode *node)
{
	Log::getInstance().write("Scale\n");
	Log::getInstance().indent();

	_s1 = node->getChild("s1")->getIntegerContent();
	Log::getInstance().write("s1: %u\n", _s1);

	_y1 = node->getChild("y1")->getIntegerContent();
	Log::getInstance().write("y1: %u\n", _y1);

	_s2 = node->getChild("s2")->getIntegerContent();
	Log::getInstance().write("s2: %u\n", _s2);

	_y2 = node->getChild("y2")->getIntegerContent();
	Log::getInstance().write("y2: %u\n", _y2);

	Log::getInstance().unIndent();
}

Scale::~Scale()
{
}

Map::Map(string dirName)
{
	Log::getInstance().write("Map\n");
	Log::getInstance().indent();

	XMLFile xmlFile(dirName + "map.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("box", i++)) != NULL)
		_boxes.push_back(new Box(child));

	i = 0;
	while ((child = rootNode->getChild("scale", i++)) != NULL)
		_scales.push_back(new Scale(child));

	Log::getInstance().unIndent();
}

Map::~Map()
{
	for (int i = 0; i < _boxes.size(); i++)
		delete _boxes[i];

	for (int i = 0; i < _scales.size(); i++)
		delete _scales[i];
}

