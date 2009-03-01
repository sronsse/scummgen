#include "Object.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Function.hpp"
#include "Game.hpp"
#include "Image.hpp"

Object::Object():
_name(""),
_displayName(""),
_imageX(0),
_imageY(0),
_x(0),
_y(0),
_width(0),
_height(0),
_flags(0),
_parent(0),
_owner(0),
_actorDir(0),
_classData(0)
{
}

void Object::load(string dirPath)
{
	XMLFile xmlFile;
	xmlFile.open(dirPath + "object.xml");
	XMLNode *node = xmlFile.getRootNode();

	Log::getInstance().write(LOG_INFO, "Object\n");
	Log::getInstance().indent();

	static uint16_t currentID = Game::N_DEFAULT_ACTORS + 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_displayName = node->getChild("displayName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "displayName: %s\n", _displayName.c_str());

	_imageX = node->getChild("imageX")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "imageX: %u\n", _imageX);

	_imageY = node->getChild("imageY")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "imageY: %u\n", _imageY);

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("hotspotX", i++)) != NULL)
		_hotspotXs.push_back(child->getIntegerContent());

	i = 0;
	while ((child = node->getChild("hotspotY", i++)) != NULL)
		_hotspotYs.push_back(child->getIntegerContent());
	
	for (i = 0; i < _hotspotXs.size(); i++)
	{
		Log::getInstance().write(LOG_INFO, "hotspotX: %d\n", _hotspotXs[i]);
		Log::getInstance().write(LOG_INFO, "hotspotY: %d\n", _hotspotYs[i]);
	}

	_x = node->getChild("x")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "x: %u\n", _x);

	_y = node->getChild("y")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "y: %u\n", _y);

	_width = node->getChild("width")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);

	_height = node->getChild("height")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	_flags = node->getChild("flags")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "flags: %u\n", _flags);

	_parent = node->getChild("parent")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "parent: %u\n", _parent);

	_owner = node->getChild("owner")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "owner: %u\n", _owner);

	_actorDir = node->getChild("actorDir")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "actorDir: %u\n", _actorDir);

	_classData = node->getChild("classData")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "classData: %x\n", _classData);

	i = 0;
	while ((child = node->getChild("image", i++)) != NULL)
	{
		Image *image = new Image();
		image->load(dirPath + child->getStringContent() + "/");
		_images.push_back(image);
	}

	_function = NULL;

	Log::getInstance().unIndent();
}

Object::~Object()
{
	for (int i = 0; i < _images.size(); i++)
		delete _images[i];
	if (_function != NULL)
		delete _function;
}
