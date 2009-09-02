#include "Object.hpp"
#include <typeinfo>
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Function.hpp"
#include "grammar/Statement.hpp"
#include "Game.hpp"
#include "Image.hpp"

const string Object::XML_FILE_NAME = "object.xml";

Object::Object():
_id(0),
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

void Object::load(string dirPath)
{
	Log::write(LOG_INFO, "Object\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	_displayName = rootNode->getChild("displayName")->getStringContent();
	Log::write(LOG_INFO, "displayName: %s\n", _displayName.c_str());

	_imageX = rootNode->getChild("imageX")->getIntegerContent();
	Log::write(LOG_INFO, "imageX: %u\n", _imageX);

	_imageY = rootNode->getChild("imageY")->getIntegerContent();
	Log::write(LOG_INFO, "imageY: %u\n", _imageY);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("hotspotX", i++)) != NULL)
		_hotspotXs.push_back(child->getIntegerContent());

	i = 0;
	while ((child = rootNode->getChild("hotspotY", i++)) != NULL)
		_hotspotYs.push_back(child->getIntegerContent());
	
	for (i = 0; i < _hotspotXs.size(); i++)
	{
		Log::write(LOG_INFO, "hotspotX: %d\n", _hotspotXs[i]);
		Log::write(LOG_INFO, "hotspotY: %d\n", _hotspotYs[i]);
	}

	_x = rootNode->getChild("x")->getIntegerContent();
	Log::write(LOG_INFO, "x: %u\n", _x);

	_y = rootNode->getChild("y")->getIntegerContent();
	Log::write(LOG_INFO, "y: %u\n", _y);

	_width = rootNode->getChild("width")->getIntegerContent();
	Log::write(LOG_INFO, "width: %u\n", _width);

	_height = rootNode->getChild("height")->getIntegerContent();
	Log::write(LOG_INFO, "height: %u\n", _height);

	_flags = rootNode->getChild("flags")->getIntegerContent();
	Log::write(LOG_INFO, "flags: %u\n", _flags);

	_parent = rootNode->getChild("parent")->getIntegerContent();
	Log::write(LOG_INFO, "parent: %u\n", _parent);

	_owner = rootNode->getChild("owner")->getIntegerContent();
	Log::write(LOG_INFO, "owner: %u\n", _owner);

	_actorDir = rootNode->getChild("actorDir")->getIntegerContent();
	Log::write(LOG_INFO, "actorDir: %u\n", _actorDir);

	_classData = rootNode->getChild("classData")->getIntegerContent();
	Log::write(LOG_INFO, "classData: %x\n", _classData);

	i = 0;
	while ((child = rootNode->getChild("image", i++)) != NULL)
	{
		Image *image = new Image();
		image->load(dirPath + child->getStringContent() + "/");
		_images.push_back(image);
	}

	Log::unIndent();
}

void Object::save(string dirPath)
{
	Log::write(LOG_INFO, "Object\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("object");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	rootNode->addChild(new XMLNode("description", _description));
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	rootNode->addChild(new XMLNode("displayName", _displayName));
	Log::write(LOG_INFO, "displayName: %s\n", _displayName.c_str());

	rootNode->addChild(new XMLNode("imageX", _imageX));
	Log::write(LOG_INFO, "imageX: %u\n", _imageX);

	rootNode->addChild(new XMLNode("imageY", _imageY));
	Log::write(LOG_INFO, "imageY: %u\n", _imageY);

	for (int i = 0; i < _hotspotXs.size(); i++)
		rootNode->addChild(new XMLNode("hotspotX", _hotspotXs[i]));

	for (int i = 0; i < _hotspotYs.size(); i++)
		rootNode->addChild(new XMLNode("hotspotY", _hotspotYs[i]));
	
	for (int i = 0; i < _hotspotXs.size(); i++)
	{
		Log::write(LOG_INFO, "hotspotX: %d\n", _hotspotXs[i]);
		Log::write(LOG_INFO, "hotspotY: %d\n", _hotspotYs[i]);
	}

	rootNode->addChild(new XMLNode("x", _x));
	Log::write(LOG_INFO, "x: %u\n", _x);

	rootNode->addChild(new XMLNode("y", _y));
	Log::write(LOG_INFO, "y: %u\n", _y);

	rootNode->addChild(new XMLNode("width", _width));
	Log::write(LOG_INFO, "width: %u\n", _width);

	rootNode->addChild(new XMLNode("height", _height));
	Log::write(LOG_INFO, "height: %u\n", _height);

	rootNode->addChild(new XMLNode("flags", _flags));
	Log::write(LOG_INFO, "flags: %u\n", _flags);

	rootNode->addChild(new XMLNode("parent", _parent));
	Log::write(LOG_INFO, "parent: %u\n", _parent);

	rootNode->addChild(new XMLNode("owner", _owner));
	Log::write(LOG_INFO, "owner: %u\n", _owner);

	rootNode->addChild(new XMLNode("actorDir", _actorDir));
	Log::write(LOG_INFO, "actorDir: %u\n", _actorDir);

	rootNode->addChild(new XMLNode("classData", (int)_classData));
	Log::write(LOG_INFO, "classData: %x\n", _classData);

	for (int i = 0; i < _images.size(); i++)
	{
		_images[i]->save(dirPath + _images[i]->getName() + '/');
		rootNode->addChild(new XMLNode("image", _images[i]->getName()));
	}

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save object to the specified directory !\n");

	Log::unIndent();
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

void Object::setPalette(Palette *palette, bool global)
{
	// Fill palette given as a parameter
	if (!_images.empty())
		_images[0]->setPalette(palette, global);
}

void Object::compile()
{
	// Check the first function statement is a verb statement and compile it
	if (typeid(*_function->getBlockStatement()->getStatement(0)) != typeid(VerbStatement))
		Log::write(LOG_ERROR, "Object \"%s\" should start with a verb statement !\n", _name.c_str());
	_function->compile();
}

Object::~Object()
{
	for (int i = 0; i < _images.size(); i++)
		delete _images[i];
	if (_function != NULL)
		delete _function;
}
