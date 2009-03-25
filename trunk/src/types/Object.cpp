#include "Object.hpp"
#include <typeinfo>
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Function.hpp"
#include "grammar/Statement.hpp"
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
_classData(0),
_function(NULL)
{
}

void Object::load(string dirPath, Palette *palette, bool global)
{
	XMLFile xmlFile;
	xmlFile.open(dirPath + "object.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	Log::getInstance().write(LOG_INFO, "Object\n");
	Log::getInstance().indent();

	static uint16_t currentID = Game::N_DEFAULT_ACTORS + 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_displayName = rootNode->getChild("displayName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "displayName: %s\n", _displayName.c_str());

	_imageX = rootNode->getChild("imageX")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "imageX: %u\n", _imageX);

	_imageY = rootNode->getChild("imageY")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "imageY: %u\n", _imageY);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("hotspotX", i++)) != NULL)
		_hotspotXs.push_back(child->getIntegerContent());

	i = 0;
	while ((child = rootNode->getChild("hotspotY", i++)) != NULL)
		_hotspotYs.push_back(child->getIntegerContent());
	
	for (i = 0; i < _hotspotXs.size(); i++)
	{
		Log::getInstance().write(LOG_INFO, "hotspotX: %d\n", _hotspotXs[i]);
		Log::getInstance().write(LOG_INFO, "hotspotY: %d\n", _hotspotYs[i]);
	}

	_x = rootNode->getChild("x")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "x: %u\n", _x);

	_y = rootNode->getChild("y")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "y: %u\n", _y);

	_width = rootNode->getChild("width")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "width: %u\n", _width);

	_height = rootNode->getChild("height")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "height: %u\n", _height);

	_flags = rootNode->getChild("flags")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "flags: %u\n", _flags);

	_parent = rootNode->getChild("parent")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "parent: %u\n", _parent);

	_owner = rootNode->getChild("owner")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "owner: %u\n", _owner);

	_actorDir = rootNode->getChild("actorDir")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "actorDir: %u\n", _actorDir);

	_classData = rootNode->getChild("classData")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "classData: %x\n", _classData);

	i = 0;
	while ((child = rootNode->getChild("image", i++)) != NULL)
	{
		Image *image = new Image();
		image->load(dirPath + child->getStringContent() + "/", palette, global);
		_images.push_back(image);
	}

	Log::getInstance().unIndent();
}

void Object::prepare()
{
	// Delete function if necessary
	if (_function != NULL)
	{
		delete _function;
		_function = NULL;
	}
}

void Object::compile()
{
	// Check the first function statement is a verb statement and compile it
	if (typeid(*_function->getBlockStatement()->getStatement(0)) != typeid(VerbStatement))
		Log::getInstance().write(LOG_ERROR, "Object \"%s\" should start with a verb statement !\n", _name.c_str());
	_function->compile();
}

Object::~Object()
{
	for (int i = 0; i < _images.size(); i++)
		delete _images[i];
	if (_function != NULL)
		delete _function;
}
