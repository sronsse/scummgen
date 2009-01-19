#include "Object.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Function.hpp"
#include "Game.hpp"
#include "Image.hpp"

Object::Object(string dirName)
{
	XMLFile xmlFile;
	xmlFile.open(dirName + "object.xml");
	XMLNode *node = xmlFile.getRootNode();

	Log::getInstance().write(LOG_INFO, "Object\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	static uint16_t currentID = Game::N_DEFAULT_ACTORS + 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	_displayName = node->getChild("displayName")->getStringContent();
	Log::getInstance().write(LOG_INFO, "displayName: %u\n", _displayName.c_str());

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

	uint16_t nZPlanes = node->getChild("nZPlanes")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "nZPlanes: %u\n", nZPlanes);

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

	loadImages(dirName, nZPlanes);

	_function = NULL;

	Log::getInstance().unIndent();
}

void Object::loadImages(string dirName, uint16_t nZPlanes)
{
	XMLFile xmlFile;
	xmlFile.open(dirName + "images.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
	{
		Log::getInstance().write(LOG_WARNING, "Object does not contain any image !\n");
		return;
	}

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("image", i++)) != NULL)
		_images.push_back(new Image(dirName + child->getStringContent() + "/", "image.bmp", nZPlanes));

	if (_images.empty())
		Log::getInstance().write(LOG_WARNING, "Object does not contain any image !\n");
}

Object::~Object()
{
	for (int i = 0; i < _images.size(); i++)
		delete _images[i];
	if (_function != NULL)
		delete _function;
}

