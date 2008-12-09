#include "Room.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "grammar/Context.hpp"
#include "grammar/Declaration.hpp"
#include "grammar/Function.hpp"
#include "grammar/Statement.hpp"
#include "Image.hpp"
#include "Palette.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "Costume.hpp"

// External flex/bison declarations
extern FILE *yyin;
extern int yyparse(vector<Declaration *> &declarations, vector<Function *> &functions);
extern int yylineno;

const uint8_t Room::MIN_LOCAL_ID = 200;

Room::Room(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Room\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	xmlFile.open(dirName + "room.xml");
	XMLNode *node = xmlFile.getRootNode();

	int posB = dirName.find_last_of('/') - 1;
	int posA = dirName.find_last_of('/', posB) + 1;
	_name = dirName.substr(posA, posB + 1 - posA);
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	static uint8_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);
	
	uint16_t nZPlanes = node->getChild("nZPlanes")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "nZPlanes: %u\n", nZPlanes);

	_background = new Image(dirName, "background.bmp", nZPlanes);
	_palette = new Palette(dirName);
	loadObjects(dirName + "objects/");
	_map = new Map(dirName);
	_entryFunction = NULL;
	_exitFunction = NULL;
	loadScripts(dirName + "scripts/");
	loadCostumes(dirName + "costumes/");

	Log::getInstance().unIndent();
}

void Room::loadObjects(string dirName)
{
	XMLFile xmlFile;
	xmlFile.open(dirName + "objects.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("object", i++)) != NULL)
		_objects.push_back(new Object(dirName + child->getStringContent() + "/"));

	// Add object declarations so that they can be used in scripts
	for (int i = 0; i < _objects.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _objects[i]->getName(), _objects[i]->getID()));
}

void Room::loadScripts(string dirName)
{
	XMLFile xmlFile;
	xmlFile.open(dirName + "scripts.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
	{
		Log::getInstance().write(LOG_WARNING, "Room doesn't contain any script !\n");
		return;
	}

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("script", i++)) != NULL)
		_scripts.push_back(dirName + child->getStringContent() + ".sgc");
}

void Room::loadCostumes(string dirName)
{
	XMLFile xmlFile;
	xmlFile.open(dirName + "costumes.xml");
	XMLNode *node = xmlFile.getRootNode();

	if (node == NULL)
		return;

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("costume", i++)) != NULL)
		_costumes.push_back(new Costume(dirName + child->getStringContent() + "/"));

	// Add costume declarations so that they can be used in scripts
	for (int i = 0; i < _costumes.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName(), _costumes[i]->getID()));
}

void Room::parse(vector<Declaration *> &declarations)
{
	Log::getInstance().write(LOG_INFO, "Parsing room \"%s\"...\n", _name.c_str());
	Log::getInstance().indent();

	if (_scripts.empty())
		Log::getInstance().write(LOG_WARNING, "Couldn't find any local script !\n");

	bool foundEntry = false;
	bool foundExit = false;
	uint16_t id = MIN_LOCAL_ID;

	for (int i = 0; i < _scripts.size(); i++)
	{
		Log::getInstance().write(LOG_INFO, "Parsing \"%s\"...\n", _scripts[i].c_str());
		yyin = fopen(_scripts[i].c_str(), "r");
		vector<Function *> functions;
		yylineno = 1;
		if (yyparse(declarations, functions))
		{
			fclose(yyin);
			for (int j = 0; j < functions.size(); j++)
				delete functions[j];
			Log::getInstance().write(LOG_ERROR, "Parsing error !\n");
		}
		for (int j = 0; j < functions.size(); j++)
			if (functions[j]->getName() == "entry")
			{
				_entryFunction = functions[j];
				foundEntry = true;
			}
			else if (functions[j]->getName() == "exit")
			{
				_exitFunction = functions[j];
				foundExit = true;
			}
			else
			{
				bool foundObject = false;
				for (int k = 0; k < _objects.size(); k++)
					if (functions[j]->getName() == _objects[k]->getName() + "_verb")
					{
						Log::getInstance().write(LOG_INFO, "Attaching \"verb\" to object \"%s\"...\n", _objects[k]->getName().c_str());
						_objects[k]->setFunction(functions[j]);
						foundObject = true;
						break;
					}

				// The current function is a simple local function
				if (!foundObject)
				{
					functions[j]->setID(id++);
					_functions.push_back(functions[j]);
				}
			}
		fclose(yyin);
	}

	// If no entry or exit function has been specified, we create empty ones
	if (!foundEntry)
	{
		Log::getInstance().write(LOG_WARNING, "Couldn't find the entry function !\n");
		_entryFunction = new Function("entry", true, new BlockStatement());
	}
	if (!foundExit)
	{
		Log::getInstance().write(LOG_WARNING, "Couldn't find the exit function !\n");
		_exitFunction = new Function("exit", true, new BlockStatement());
	}

	Log::getInstance().unIndent();
}

void Room::compile()
{
	Log::getInstance().write(LOG_INFO, "Compiling room \"%s\"...\n", _name.c_str());
	Log::getInstance().indent();	

	Context context(CONTEXT_ROOM, &_declarations, &_functions, -1, -1, -1);
	Context::pushContext(&context);
	
	// We compile the common functions
	for (int i = 0; i < _functions.size(); i++)
		_functions[i]->compile();

	// Then we compile the entry and exit functions
	_entryFunction->compile();
	_exitFunction->compile();

	// Finally we compile the object functions
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->getFunction() != NULL)
			_objects[i]->getFunction()->compile();

	Context::popContext();

	Log::getInstance().unIndent();
}

Room::~Room()
{
	delete _background;
	delete _palette;
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];
	delete _map;
	for (int i = 0; i < _costumes.size(); i++)
		delete _costumes[i];
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	delete _entryFunction;
	delete _exitFunction;
	for (int i = 0; i < _functions.size(); i++)
		delete _functions[i];
}
