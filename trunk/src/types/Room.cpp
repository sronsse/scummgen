#include "Room.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Context.hpp"
#include "grammar/Declaration.hpp"
#include "grammar/Statement.hpp"
#include "Costume.hpp"
#include "Image.hpp"
#include "Map.hpp"
#include "Object.hpp"
#include "Palette.hpp"
#include "Script.hpp"

const string Room::XML_FILE_NAME = "room.xml";
const uint8_t Room::MIN_LOCAL_SCRIPT_ID = 200;

Room::Room():
_id(0),
_name(""),
_background(NULL),
_paletteData(NULL),
_palette(NULL),
_map(NULL),
_script(NULL),
_entryFunction(NULL),
_exitFunction(NULL)
{	
}

void Room::loadObjects(string dirPath, XMLNode *node)
{
	dirPath += "objects/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("object", i++)) != NULL)
	{
		Object *object = new Object();
		object->load(dirPath + child->getStringContent() + '/');
		_objects.push_back(object);
	}
}

void Room::loadCostumes(string dirPath, XMLNode *node)
{
	dirPath += "costumes/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("costume", i++)) != NULL)
	{
		Costume *costume = new Costume();
		costume->load(dirPath + child->getStringContent() + '/');
		_costumes.push_back(costume);
	}
}

void Room::saveObjects(string dirPath, XMLNode *node)
{
	if (_objects.empty())
		return;

	dirPath += "objects/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->save(dirPath + _objects[i]->getName() + '/');
		node->addChild(new XMLNode("object", _objects[i]->getName()));
	}
}

void Room::saveCostumes(string dirPath, XMLNode *node)
{
	if (_costumes.empty())
		return;

	dirPath += "costumes/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _costumes.size(); i++)
	{
		_costumes[i]->save(dirPath + _costumes[i]->getName() + '/');
		node->addChild(new XMLNode("costume", _costumes[i]->getName()));
	}
}

void Room::load(string dirPath)
{
	Log::write(LOG_INFO, "Room\n");
	Log::indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + XML_FILE_NAME);
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_palette = new Palette(true);

	_background = new Image();
	_background->load(dirPath + rootNode->getChild("background")->getStringContent() + '/');

	_map = new Map;
	_map->load(dirPath);

	_script = new Script();
	_script->load(dirPath + rootNode->getChild("script")->getStringContent() + '/');

	loadObjects(dirPath, rootNode);
	loadCostumes(dirPath, rootNode);

	_paletteData = new PaletteData();
	_paletteData->load(dirPath);

	Log::unIndent();
}

void Room::save(string dirPath)
{
	Log::write(LOG_INFO, "Room\n");
	Log::indent();

	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("room");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_background->save(dirPath + _background->getName() + '/');
	rootNode->addChild(new XMLNode("background", _background->getName()));

	_map->save(dirPath);

	_script->save(dirPath + _script->getName() + '/');
	rootNode->addChild(new XMLNode("script", _script->getName()));

	saveObjects(dirPath, rootNode);
	saveCostumes(dirPath, rootNode);

	_paletteData->save(dirPath);

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save room to the specified directory !\n");

	Log::unIndent();
}

void Room::prepare()
{
	Log::write(LOG_INFO, "Preparing room %s...\n", _name.c_str());
	Log::indent();

	// Prepare palette
	_palette->prepare();

	// Prepare background
	_background->prepare(_palette, _paletteData);

	// Prepare map
	_map->prepare();

	// Prepare objects
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->prepare(_palette);	

	// Prepare costumes
	for (int i = 0; i < _costumes.size(); i++)
		_costumes[i]->prepare(_palette);

	// Clear declarations and functions
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	_declarations.clear();
	if (_entryFunction != NULL)
	{
		delete _entryFunction;
		_entryFunction = NULL;
	}
	if (_exitFunction != NULL)
	{
		delete _exitFunction;
		_exitFunction = NULL;
	}
	for (int i = 0; i < _functions.size(); i++)
		delete _functions[i];
	_functions.clear();

	Log::write(LOG_INFO, "Palette cursor: %u\n", _palette->getCursor());
	Log::unIndent();
}

void Room::parse(vector<Declaration *> &declarations)
{
	Log::write(LOG_INFO, "Parsing room \"%s\"...\n", _name.c_str());
	Log::indent();

	uint16_t id = MIN_LOCAL_SCRIPT_ID;

	// Parse the local script
	vector<Function *> functions;
	_script->parse(declarations, functions);

	for (int i = 0; i < functions.size(); i++)
		if (functions[i]->getName() == _name + "_entry")
		{
			if (functions[i]->getType() == FUNCTION_INLINED)
				Log::write(LOG_ERROR, "Function \"entry\" can't be inlined !\n");
			_entryFunction = functions[i];
		}
		else if (functions[i]->getName() == _name + "_exit")
		{
			if (functions[i]->getType() == FUNCTION_INLINED)
				Log::write(LOG_ERROR, "Function \"exit\" can't be inlined !\n");
			_exitFunction = functions[i];
		}
		else
		{
			bool foundObject = false;
			for (int j = 0; j < _objects.size(); j++)
				if (functions[i]->getName() == _objects[j]->getName() + "_verb")
				{
					if (functions[i]->getType() == FUNCTION_INLINED)
						Log::write(LOG_ERROR, "Function \"%s\" can't be inlined !\n", functions[i]->getName().c_str());
					Log::write(LOG_INFO, "Attaching \"verb\" to object \"%s\"...\n", _objects[j]->getName().c_str());
					_objects[j]->setFunction(functions[i]);
					foundObject = true;
					break;
				}

			// The current function is a simple local function
			if (!foundObject)
			{
				if (functions[i]->getType() != FUNCTION_INLINED)
					functions[i]->setID(id++);
				_functions.push_back(functions[i]);
			}
		}

	// If no entry or exit function has been specified, we create empty ones
	if (_entryFunction == NULL)
	{
		Log::write(LOG_WARNING, "Couldn't find the entry function !\n");
		_entryFunction = new Function(FUNCTION_NORMAL, "entry", new BlockStatement());
	}
	if (_exitFunction == NULL)
	{
		Log::write(LOG_WARNING, "Couldn't find the exit function !\n");
		_exitFunction = new Function(FUNCTION_NORMAL, "exit", new BlockStatement());
	}

	// Areas declarations
	for (int i = 0; i < _palette->getNumberOfAreas(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getArea(i)->getName() + "_start", _palette->getArea(i)->getStart()));
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getArea(i)->getName() + "_end", _palette->getArea(i)->getEnd()));
	}

	// Cycles declarations
	for (int i = 0; i < _palette->getNumberOfCycles(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getCycle(i)->getName(), _palette->getCycle(i)->getID()));

	// Costumes declarations
	for (int i = 0; i < _costumes.size(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName(), _costumes[i]->getID()));
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
			_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName() + "_" + _costumes[i]->getAnim(j)->getName(), _costumes[i]->getAnim(j)->getID()));
	}

	// Boxes declarations
	for (int i = 0; i < _map->getNumberOfBoxes(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _map->getBox(i)->getName(), _map->getBox(i)->getID()));

	Log::unIndent();
}

void Room::compile()
{
	Log::write(LOG_INFO, "Compiling room \"%s\"...\n", _name.c_str());
	Log::indent();

	Context context(CONTEXT_ROOM, &_declarations, NULL, -1, -1, -1);
	Context::pushContext(&context);

	// Compile the entry and exit functions
	_entryFunction->compile();
	_exitFunction->compile();

	// Compile local functions
	for (int i = 0; i < _functions.size(); i++)
		if (_functions[i]->getType() != FUNCTION_INLINED)
			_functions[i]->compile();

	// Compile objects
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->compile();

	Context::popContext();

	Log::unIndent();
}

Room::~Room()
{
	if (_background != NULL)
		delete _background;
	if (_paletteData != NULL)
		delete _paletteData;
	if (_palette != NULL)
		delete _palette;
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];
	if (_map != NULL)
		delete _map;
	if (_script != NULL)
		delete _script;
	for (int i = 0; i < _costumes.size(); i++)
		delete _costumes[i];
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	if (_entryFunction != NULL)
		delete _entryFunction;
	if (_exitFunction != NULL)
		delete _exitFunction;
	for (int i = 0; i < _functions.size(); i++)
		delete _functions[i];
}
