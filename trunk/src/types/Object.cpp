#include "Object.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Image.hpp"
#include "Script.hpp"

Object::Object(string dirName, uint32_t nZPlanes)
{
	XMLFile xmlFile(dirName + "object.xml");
	XMLNode *node = xmlFile.getRootNode();

	Log::getInstance().write("Object\n");
	Log::getInstance().indent();

	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write("name: %s\n", _name.c_str());

	_nImages = node->getChild("nImages")->getIntegerContent();
	Log::getInstance().write("nImages: %u\n", _nImages);

	bool bomp = node->getChild("bomp")->getBooleanContent();
	Log::getInstance().write("bomp: %s\n", bomp ? "true" : "false");

	_x = node->getChild("x")->getIntegerContent();
	Log::getInstance().write("x: %u\n", _x);

	_y = node->getChild("y")->getIntegerContent();
	Log::getInstance().write("y: %u\n", _y);

	_width = node->getChild("width")->getIntegerContent();
	Log::getInstance().write("width: %u\n", _width);

	_height = node->getChild("height")->getIntegerContent();
	Log::getInstance().write("height: %u\n", _height);

	_hotSpotX = node->getChild("hotSpotX")->getIntegerContent();
	Log::getInstance().write("hotSpotX: %u\n", _hotSpotX);

	_hotSpotY = node->getChild("hotSpotY")->getIntegerContent();
	Log::getInstance().write("hotSpotY: %u\n", _hotSpotY);

	_id = node->getChild("id")->getIntegerContent();
	Log::getInstance().write("id: %u\n", _id);

	_parent = node->getChild("parent")->getIntegerContent();
	Log::getInstance().write("parent: %u\n", _parent);

	_parentState = node->getChild("parentState")->getIntegerContent();
	Log::getInstance().write("parentState: %u\n", _parentState);

	_displayName = node->getChild("displayName")->getStringContent();
	Log::getInstance().write("displayName: %s\n", _displayName.c_str());

	_classData = node->getChild("classData")->getIntegerContent();
	Log::getInstance().write("classData: %u\n", _classData);

	for (int i = 0; i < _nImages; i++)
		_images.push_back(new Image(dirName + "images/image_" + IO::getStringFromIndex(i, 3) + "/", "image.bmp", bomp, nZPlanes));

	_script = new Script(dirName + "verb.txt");

	Log::getInstance().unIndent();
}

Object::~Object()
{
	for (int i = 0; i < _images.size(); i++)
		delete _images[i];
	delete _script;
}

