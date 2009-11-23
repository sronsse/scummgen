#include "Room.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Context.hpp"
#include "grammar/Declaration.hpp"
#include "grammar/Statement.hpp"
#include "Image.hpp"
#include "Palette.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Script.hpp"
#include "Costume.hpp"

const string Room::XML_FILE_NAME = "room.xml";
const uint8_t Room::MIN_LOCAL_SCRIPT_ID = 200;

Room::Room():
_id(0),
_name(""),
_background(NULL),
_palette(NULL),
_map(NULL),
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

void Room::loadScripts(string dirPath, XMLNode *node)
{
	dirPath += "scripts/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("script", i++)) != NULL)
	{
		Script *script = new Script();
		script->load(dirPath + child->getStringContent() + '/');
		_scripts.push_back(script);
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

void Room::saveScripts(string dirPath, XMLNode *node)
{
	if (_scripts.empty())
		return;

	dirPath += "scripts/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _scripts.size(); i++)
	{
		_scripts[i]->save(dirPath + _scripts[i]->getName() + '/');
		node->addChild(new XMLNode("script", _scripts[i]->getName()));
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

	_palette = new Palette();

	_background = new Image();
	_background->load(dirPath + rootNode->getChild("background")->getStringContent() + '/');

	_map = new Map;
	_map->load(dirPath);

	loadObjects(dirPath, rootNode);
	loadScripts(dirPath, rootNode);
	loadCostumes(dirPath, rootNode);

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

	saveObjects(dirPath, rootNode);
	saveScripts(dirPath, rootNode);
	saveCostumes(dirPath, rootNode);

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save room to the specified directory !\n");

	Log::unIndent();
}

void Room::prepare()
{
	// Prepare palette
	_palette->prepare();

	// Set background palette
	_background->fillPalette(_palette, false);

	// Prepare map
	_map->prepare();

	// Prepare objects and fill the room palette accordingly
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->prepare();
		_objects[i]->fillPalette(_palette, false);
	}

	// Prepare costumes and fill the room palette accordingly
	for (int i = 0; i < _costumes.size(); i++)
	{
		_costumes[i]->prepare();
		_costumes[i]->fillPalette(_palette, false);
	}

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
}

void Room::parse(vector<Declaration *> &declarations)
{
	Log::write(LOG_INFO, "Parsing room \"%s\"...\n", _name.c_str());
	Log::indent();

	bool foundEntry = false;
	bool foundExit = false;
	uint16_t id = MIN_LOCAL_SCRIPT_ID;

	// Parse all the local scripts
	for (int i = 0; i < _scripts.size(); i++)
	{
		vector<Function *> functions;
		_scripts[i]->parse(declarations, functions);

		// Check if local variables have fixed addresses
		for (int j = 0; j < declarations.size(); j++)
			if (declarations[i]->hasFixedAddress())
				Log::write(LOG_ERROR, "Local variables can't have fixed addresses !\n");

		for (int j = 0; j < functions.size(); j++)
			if (functions[j]->getName() == "entry")
			{
				if (functions[j]->getType() == FUNCTION_INLINED)
					Log::write(LOG_ERROR, "Function \"entry\" can't be inlined !\n");
				_entryFunction = functions[j];
				foundEntry = true;
			}
			else if (functions[j]->getName() == "exit")
			{
				if (functions[j]->getType() == FUNCTION_INLINED)
					Log::write(LOG_ERROR, "Function \"exit\" can't be inlined !\n");
				_exitFunction = functions[j];
				foundExit = true;
			}
			else
			{
				bool foundObject = false;
				for (int k = 0; k < _objects.size(); k++)
					if (functions[j]->getName() == _objects[k]->getName() + "_verb")
					{
						if (functions[j]->getType() == FUNCTION_INLINED)
							Log::write(LOG_ERROR, "Function \"%s\" can't be inlined !\n", functions[j]->getName().c_str());
						Log::write(LOG_INFO, "Attaching \"verb\" to object \"%s\"...\n", _objects[k]->getName().c_str());
						_objects[k]->setFunction(functions[j]);
						foundObject = true;
						break;
					}

				// The current function is a simple local function
				if (!foundObject)
				{
					if (functions[j]->getType() != FUNCTION_INLINED)
						functions[j]->setID(id++);
					_functions.push_back(functions[j]);
				}
			}
	}

	// If no entry or exit function has been specified, we create empty ones
	if (!foundEntry)
	{
		Log::write(LOG_WARNING, "Couldn't find the entry function !\n");
		_entryFunction = new Function(FUNCTION_NORMAL, "entry", new BlockStatement());
	}
	if (!foundExit)
	{
		Log::write(LOG_WARNING, "Couldn't find the exit function !\n");
		_exitFunction = new Function(FUNCTION_NORMAL, "exit", new BlockStatement());
	}

	// Add empty object functions if necessary
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->getFunction() == NULL)
		{
			VerbStatement *vs = new VerbStatement();
			BlockStatement *bs = new BlockStatement();
			bs->addStatement(vs);
			Function *f = new Function(FUNCTION_NORMAL, _objects[i]->getName() + "_verb", bs);
			_objects[i]->setFunction(f);
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

	Context context(CONTEXT_ROOM, &_declarations, &_functions, -1, -1, -1);
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
	if (_palette != NULL)
		delete _palette;
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];
	if (_map != NULL)
		delete _map;
	for (int i = 0; i < _scripts.size(); i++)
		delete _scripts[i];
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
