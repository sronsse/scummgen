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

	static uint8_t currentID = 1;
	_id = currentID++;
	Log::getInstance().write(LOG_INFO, "id: %u\n", _id);

	XMLFile xmlFile;
	xmlFile.open(dirPath + "room.xml");
	XMLNode *node = xmlFile.getRootNode();

	_name = node->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_background = new Image();
	_background->load(dirPath + node->getChild("background")->getStringContent() + "/");
	_palette = new Palette(dirPath);
	loadObjects(dirPath, node);
	_map = new Map;
	_map->load(dirPath + node->getChild("map")->getStringContent() + "/");
	loadScripts(dirPath, node);
	loadCostumes(dirPath, node);

	addDeclarations();

	Log::getInstance().unIndent();
}

void Room::loadObjects(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("object", i++)) != NULL)
	{
		Object *object = new Object();
		object->load(dirPath + child->getStringContent() + "/");
		_objects.push_back(object);
	}
}

void Room::loadScripts(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("script", i++)) != NULL)
		_scripts.push_back(dirPath + child->getStringContent());
}

void Room::loadCostumes(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("costume", i++)) != NULL)
	{
		Costume *costume = new Costume();
		costume->load(dirPath + child->getStringContent() + "/");
		_costumes.push_back(costume);
	}
}

void Room::addDeclarations()
{
	Log::getInstance().write(LOG_INFO, "Adding room local resource declarations...\n");
	Log::getInstance().indent();

	// Palette cycles declarations
	for (int i = 0; i < _palette->getNumberOfCycles(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getCycle(i)->getName(), _palette->getCycle(i)->getID()));

	// Object declarations
	for (int i = 0; i < _objects.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _objects[i]->getName(), _objects[i]->getID()));

	// Costume declarations
	for (int i = 0; i < _costumes.size(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName(), _costumes[i]->getID()));
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
		{
			Anim *anim = _costumes[i]->getAnim(j);
			_declarations.push_back(new Declaration(DECLARATION_CONST, anim->getName(), anim->getID()));
		}
	}

	// Box declarations
	for (int i = 0; i < _map->getNumberOfBoxes(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _map->getBox(i)->getName(), _map->getBox(i)->getID()));

	Log::getInstance().unIndent();
}

#if 0
void Room::updatePalette()
{
	uint16_t nOriginalColors = _palette->getNumberOfColors();
	vector<Color> localColors;

	// Add the colors of the room objects to our array of local colors
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->getNumberOfImages() > 0)
		{
			for (int j = 0; j < _objects[i]->getNumberOfImages(); j++)
				_objects[i]->getImage(j)->setPaletteBaseIndex(nOriginalColors + localColors.size());

			for (int j = 0; j < _objects[i]->getImage(0)->getNumberOfColors(); j++)
				localColors.push_back(_objects[i]->getImage(0)->getColor(j));
		}

	// Add the colors of the room costumes to our array of local colors
	/*for (int i = 0; i < _costumes.size(); i++)
	{
		_costumes[i]->setPaletteBaseIndex(nOriginalColors + localColors.size());

		for (int j = 0; j < _costumes[i]->getNumberOfColors(); j++)
			localColors.push_back(_costumes[i]->getColor(j));
	}*/

	// Update room palette
	if (_palette->getNumberOfColors() + localColors.size() > Palette::MAX_COLORS)
		Log::getInstance().write(LOG_ERROR, "The local computed palette is too big to be inserted !\n");

	_palette->resize(_palette->getNumberOfColors() + localColors.size());

	for (int i = 0; i < localColors.size(); i++)
		_palette->setColor(nOriginalColors + i, localColors[i]);
}
#endif

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
		fclose(yyin);
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
	for (int i = 0; i < _objects.size(); i++)
		if (_objects[i]->getFunction() == NULL)
			_objects[i]->setFunction(new Function(FUNCTION_NORMAL, _objects[i]->getName() + "_verb", new BlockStatement()));

	Log::getInstance().unIndent();
}

void Room::compile()
{
	Log::getInstance().write(LOG_INFO, "Compiling room \"%s\"...\n", _name.c_str());
	Log::getInstance().indent();

	Context context(CONTEXT_ROOM, &_declarations, &_functions, -1, -1, -1);
	Context::pushContext(&context);

	// We compile local functions
	for (int i = 0; i < _functions.size(); i++)
		if (_functions[i]->getType() != FUNCTION_INLINED)
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
	if (_background != NULL)
		delete _background;
	if (_palette != NULL)
		delete _palette;
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];
	if (_map != NULL)
		delete _map;
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
