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

void Room::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Room\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirPath + "room.xml");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_palette = new Palette();
	_palette->load(dirPath);

	_background = new Image();
	_background->load(dirPath + rootNode->getChild("background")->getStringContent() + "/", _palette, false);

	_map = new Map;
	_map->load(dirPath);

	loadObjects(dirPath, rootNode);
	loadScripts(dirPath, rootNode);
	loadCostumes(dirPath, rootNode);

	Log::getInstance().unIndent();
}

void Room::loadObjects(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("object", i++)) != NULL)
	{
		Object *object = new Object();
		object->load(dirPath + child->getStringContent() + "/", _palette, false);
		_objects.push_back(object);
	}
}

void Room::loadScripts(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("script", i++)) != NULL)
	{
		Script *script = new Script();
		script->load(dirPath + child->getStringContent() + "/");
		_scripts.push_back(script);
	}

	if (_scripts.empty())
		Log::getInstance().write(LOG_WARNING, "Couldn't find any local script !\n");
}

void Room::loadCostumes(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("costume", i++)) != NULL)
	{
		Costume *costume = new Costume();
		costume->load(dirPath + child->getStringContent() + "/", _palette, false);
		_costumes.push_back(costume);
	}
}

void Room::prepare()
{
	// Prepare resources
	_palette->prepare();
	_map->prepare();
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->prepare();

	// Set resource IDs
	for (int i = 0; i < _costumes.size(); i++)
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
			_costumes[i]->getAnim(j)->setID(j);

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
	Log::getInstance().write(LOG_INFO, "Parsing room \"%s\"...\n", _name.c_str());
	Log::getInstance().indent();

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
				Log::getInstance().write(LOG_ERROR, "Local variables can't have fixed addresses !\n");

		for (int j = 0; j < functions.size(); j++)
			if (functions[j]->getName() == "entry")
			{
				if (functions[j]->getType() == FUNCTION_INLINED)
					Log::getInstance().write(LOG_ERROR, "Function \"entry\" can't be inlined !\n");
				_entryFunction = functions[j];
				foundEntry = true;
			}
			else if (functions[j]->getName() == "exit")
			{
				if (functions[j]->getType() == FUNCTION_INLINED)
					Log::getInstance().write(LOG_ERROR, "Function \"exit\" can't be inlined !\n");
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
							Log::getInstance().write(LOG_ERROR, "Function \"%s\" can't be inlined !\n", functions[j]->getName().c_str());
						Log::getInstance().write(LOG_INFO, "Attaching \"verb\" to object \"%s\"...\n", _objects[k]->getName().c_str());
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
		Log::getInstance().write(LOG_WARNING, "Couldn't find the entry function !\n");
		_entryFunction = new Function(FUNCTION_NORMAL, "entry", new BlockStatement());
	}
	if (!foundExit)
	{
		Log::getInstance().write(LOG_WARNING, "Couldn't find the exit function !\n");
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

	// Set local resources declarations
	for (int i = 0; i < _palette->getNumberOfCycles(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getCycle(i)->getName(), _palette->getCycle(i)->getID()));
	for (int i = 0; i < _objects.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _objects[i]->getName(), _objects[i]->getID()));
	for (int i = 0; i < _costumes.size(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName(), _costumes[i]->getID()));
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
			_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName() + "_" + _costumes[i]->getAnim(j)->getName(), _costumes[i]->getAnim(j)->getID()));
	}
	for (int i = 0; i < _map->getNumberOfBoxes(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _map->getBox(i)->getName(), _map->getBox(i)->getID()));

	Log::getInstance().unIndent();
}

void Room::compile()
{
	Log::getInstance().write(LOG_INFO, "Compiling room \"%s\"...\n", _name.c_str());
	Log::getInstance().indent();

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

	Log::getInstance().unIndent();
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
