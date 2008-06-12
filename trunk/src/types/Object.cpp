#include "Object.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "Image.hpp"
#include "Script.hpp"

vector<Object *> Object::_instances;

Object *Object::getInstanceFromName(string objectName)
{
	for (int i = 0; i < _instances.size(); i++)
		if (_instances[i]->getName() == objectName)
			return _instances[i];
	return NULL;
}

Object::Object(string dirName)
{
	XMLFile xmlFile(dirName + "object.xml");
	XMLNode *node = xmlFile.getRootNode();

	_instances.push_back(this);

	Log::getInstance().write("Object\n");
	Log::getInstance().indent();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write("name: %s\n", _name.c_str());

	_id = _instances.size();
	Log::getInstance().write("id: %u\n", _id);

	_imageX = node->getChild("imageX")->getIntegerContent();
	Log::getInstance().write("imageX: %u\n", _imageX);

	_imageY = node->getChild("imageY")->getIntegerContent();
	Log::getInstance().write("imageY: %u\n", _imageY);

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("hotspotX", i++)) != NULL)
		_hotspotXs.push_back(child->getIntegerContent());

	i = 0;
	while ((child = node->getChild("hotspotY", i++)) != NULL)
		_hotspotYs.push_back(child->getIntegerContent());
	
	for (i = 0; i < _hotspotXs.size(); i++)
	{
		Log::getInstance().write("hotspotX: %d\n", _hotspotXs[i]);
		Log::getInstance().write("hotspotY: %d\n", _hotspotYs[i]);
	}

	_x = node->getChild("x")->getIntegerContent();
	Log::getInstance().write("x: %u\n", _x);

	uint16_t nZPlanes = node->getChild("nZPlanes")->getIntegerContent();
	Log::getInstance().write("nZPlanes: %u\n", nZPlanes);

	_y = node->getChild("y")->getIntegerContent();
	Log::getInstance().write("y: %u\n", _y);

	_width = node->getChild("width")->getIntegerContent();
	Log::getInstance().write("width: %u\n", _width);

	_height = node->getChild("height")->getIntegerContent();
	Log::getInstance().write("height: %u\n", _height);

	_flags = node->getChild("flags")->getIntegerContent();
	Log::getInstance().write("flags: %u\n", _flags);

	_parent = node->getChild("parent")->getIntegerContent();
	Log::getInstance().write("parent: %u\n", _parent);

	_actorDir = node->getChild("actorDir")->getIntegerContent();
	Log::getInstance().write("actorDir: %u\n", _actorDir);

	_classData = node->getChild("classData")->getIntegerContent();
	Log::getInstance().write("classData: %u\n", _classData);

	loadImages(dirName + "images/", nZPlanes);
	_script = new Script(dirName + "verb" + Script::EXTENSION, Script::TYPE_OTHER);

	Log::getInstance().unIndent();
}

void Object::loadImages(string dirName, uint16_t nZPlanes)
{
	XMLFile xmlFile(dirName + "images.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("image", i++)) != NULL)
		_images.push_back(new Image(dirName + child->getStringContent() + "/", "image.bmp", nZPlanes));
}

Object::~Object()
{
	for (int i = 0; i < _images.size(); i++)
		delete _images[i];
	delete _script;
}

