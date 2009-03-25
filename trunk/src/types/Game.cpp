#include "Game.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/XMLFile.hpp"
#include "blocks/RNAM.hpp"
#include "blocks/MAXS.hpp"
#include "blocks/DROO.hpp"
#include "blocks/DSCR.hpp"
#include "blocks/DSOU.hpp"
#include "blocks/DCOS.hpp"
#include "blocks/DCHR.hpp"
#include "blocks/DOBJ.hpp"
#include "blocks/AARY.hpp"
#include "blocks/LECF.hpp"
#include "blocks/SOU2.hpp"
#include "grammar/Context.hpp"
#include "grammar/Declaration.hpp"
#include "grammar/Function.hpp"
#include "grammar/Statement.hpp"
#include "Room.hpp"
#include "Object.hpp"
#include "Midi.hpp"
#include "Script.hpp"
#include "Costume.hpp"
#include "Charset.hpp"
#include "Voice.hpp"
#include "Image.hpp"
#include "Palette.hpp"

const char *Game::INDEX_FILE_EXTENSION = ".000";
const char *Game::RESOURCE_FILE_EXTENSION = ".001";
const char *Game::VOICE_FILE_NAME = "MONSTER.SOU";

const uint8_t Game::N_DEFAULT_ACTORS = 12;
const uint16_t Game::MAX_WORD_VARIABLES = 8192;
const uint8_t Game::MAX_LOCAL_VARIABLES = 16;

Array::Array():
_varNumber(0),
_dimA(0),
_dimB(0),
_type(0)
{
}

void Array::load(XMLNode *node)
{
	Log::getInstance().write(LOG_INFO, "Array\n");
	Log::getInstance().indent();

	_varNumber = node->getChild("varNumber")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "varNumber: %u\n", _varNumber);

	_dimA = node->getChild("dimA")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "dimA: %u\n", _dimA);

	_dimB = node->getChild("dimB")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "dimB: %u\n", _dimB);

	_type = node->getChild("type")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "type: %u\n", _type);

	Log::getInstance().unIndent();
}

Array::~Array()
{
}

Game::Game():
_name(""),
_description(""),
_key(0)
{
}

void Game::load(string dirPath)
{
	Log::getInstance().write(LOG_INFO, "Game\n");
	Log::getInstance().indent();

	XMLFile xmlFile;
	if (!xmlFile.open(dirPath + "game.xml"))
		Log::getInstance().write(LOG_ERROR, "Couldn't find any game in the specified directory !\n");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::getInstance().write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::getInstance().write(LOG_INFO, "description: %s\n", _description.c_str());

	_key = rootNode->getChild("key")->getIntegerContent();
	Log::getInstance().write(LOG_INFO, "key: 0x%02x\n", _key);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("array", i++)) != NULL)
	{
		Array *array = new Array();
		array->load(child);
		_arrays.push_back(array);
	}

	loadRooms(dirPath, rootNode);
	loadObjects(dirPath, rootNode);
	loadMidis(dirPath, rootNode);
	loadCostumes(dirPath, rootNode);
	loadScripts(dirPath, rootNode);
	loadCharsets(dirPath, rootNode);
	loadVoices(dirPath, rootNode);

	Log::getInstance().unIndent();
}

void Game::loadRooms(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("room", i++)) != NULL)
	{
		Room *room = new Room();
		room->load(dirPath + child->getStringContent() + "/");
		_rooms.push_back(room);
	}

	if (_rooms.empty())
		Log::getInstance().write(LOG_WARNING, "Game does not contain any room !\n");
}

void Game::loadObjects(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("object", i++)) != NULL)
	{
		Object *object = new Object();
		object->load(dirPath + child->getStringContent() + "/", _rooms[0]->getPalette(), true);
		_objects.push_back(object);
	}

	if (_objects.empty())
		Log::getInstance().write(LOG_WARNING, "Game does not contain any global object !\n");
}

void Game::loadMidis(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("midi", i++)) != NULL)
	{
		Midi *midi = new Midi();
		midi->load(dirPath + child->getStringContent() + "/");
		_midis.push_back(midi);
	}

	if (_midis.empty())
		Log::getInstance().write(LOG_WARNING, "Game does not contain any music !\n");
}

void Game::loadCostumes(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("costume", i++)) != NULL)
	{
		Costume *costume = new Costume();
		costume->load(dirPath + child->getStringContent() + "/", _rooms[0]->getPalette(), true);
		_costumes.push_back(costume);
	}

	if (_costumes.empty())
		Log::getInstance().write(LOG_WARNING, "Game does not contain any global costume !\n");
}

void Game::loadScripts(string dirPath, XMLNode *node)
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
		Log::getInstance().write(LOG_ERROR, "Couldn't find any global script !\n");
}

void Game::loadCharsets(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("charset", i++)) != NULL)
	{
		Charset *charset = new Charset();
		charset->load(dirPath + child->getStringContent() + "/");
		_charsets.push_back(charset);
	}

	if (_charsets.empty())
		Log::getInstance().write(LOG_WARNING, "Game does not contain any charset !\n");
}

void Game::loadVoices(string dirPath, XMLNode *node)
{
	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("voice", i++)) != NULL)
	{
		Voice *voice;
		voice->load(dirPath + child->getStringContent() + "/");
		_voices.push_back(voice);
	}

	if (_voices.empty())
		Log::getInstance().write(LOG_WARNING, "Game does not contain any voice !\n");
}

void Game::prepare()
{
	// Prepare objects
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->prepare();

	// Prepare rooms
	for (int i = 0; i < _rooms.size(); i++)
		_rooms[i]->prepare();

	// Set resource IDs
	uint8_t currentRoomID = 1;
	uint16_t currentObjectID = N_DEFAULT_ACTORS + 1;
	uint16_t currentMidiID = 1;
	uint16_t currentCostumeID = 1;
	uint16_t currentCharsetID = 1;
	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i]->setID(currentRoomID++);
		for (int j = 0; j < _rooms[i]->getNumberOfObjects(); j++)
			_rooms[i]->getObject(j)->setID(currentObjectID++);
		for (int j = 0; j < _rooms[i]->getNumberOfCostumes(); j++)
			_rooms[i]->getCostume(j)->setID(currentCostumeID++);
	}
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->setID(currentObjectID++);
	for (int i = 0; i < _midis.size(); i++)
		_midis[i]->setID(currentMidiID++);
	for (int i = 0; i < _costumes.size(); i++)
	{
		_costumes[i]->setID(currentCostumeID++);
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
			_costumes[i]->getAnim(j)->setID(j);
	}
	for (int i = 0; i < _charsets.size(); i++)
		_charsets[i]->setID(currentCharsetID++);

	// Clear declarations and functions
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	_declarations.clear();
	for (int i = 0; i < _functions.size(); i++)
		delete _functions[i];
	_functions.clear();
}

void Game::parse()
{
	Log::getInstance().write(LOG_INFO, "Parsing game...\n");
	Log::getInstance().indent();

	bool foundMain = false;
	uint16_t id = 2; // id 1 is reserved for the main function

	// Parse global scripts
	for (int i = 0; i < _scripts.size(); i++)
	{
		vector<Function *> functions;
		_scripts[i]->parse(_declarations, functions);

		for (int j = 0; j < functions.size(); j++)
			// Special case for the main function
			if (functions[j]->getName() == "main")
			{
				if (functions[j]->getType() == FUNCTION_INLINED)
					Log::getInstance().write(LOG_ERROR, "Function \"main\" can't be inlined !\n");
				functions[j]->setID(1);
				_functions.insert(_functions.begin(), functions[j]);
				foundMain = true;
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

				// The current function is a simple global function
				if (!foundObject)
				{
					if (functions[j]->getType() != FUNCTION_INLINED)
						functions[j]->setID(id++);
					_functions.push_back(functions[j]);
				}
			}
	}

	// Check if the game main entry point has been found
	if (!foundMain)
		Log::getInstance().write(LOG_ERROR, "Couldn't find the main function !\n");

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

	// Set global resources declarations
	for (int i = 0; i < _objects.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _objects[i]->getName(), _objects[i]->getID()));
	for (int i = 0; i < _midis.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _midis[i]->getName(), _midis[i]->getID()));
	for (int i = 0; i < _costumes.size(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName(), _costumes[i]->getID()));
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
			_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName() + "_" + _costumes[i]->getAnim(j)->getName(), _costumes[i]->getAnim(j)->getID()));
	}
	for (int i = 0; i < _charsets.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _charsets[i]->getName(), _charsets[i]->getID()));
	for (int i = 0; i < _rooms.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _rooms[i]->getName(), _rooms[i]->getID()));

	// Parse rooms
	for (int i = 0; i < _rooms.size(); i++)
		_rooms[i]->parse(_declarations);

	Log::getInstance().unIndent();
}

void Game::compile()
{
	Log::getInstance().write(LOG_INFO, "Compiling game scripts...\n");
	Log::getInstance().indent();

	Context context(CONTEXT_GAME, &_declarations, &_functions, -1, -1, -1);
	Context::pushContext(&context);

	// Compile global functions
	for (int i = 0; i < _functions.size(); i++)
		if (_functions[i]->getType() != FUNCTION_INLINED)
			_functions[i]->compile();

	// Compile objects
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->compile();

	// Compile rooms
	for (int i = 0; i < _rooms.size(); i++)
		_rooms[i]->compile();

	Context::popContext();

	Log::getInstance().unIndent();
}

void Game::generate(string outputDirPath)
{
	Log::getInstance().write(LOG_INFO, "Generating game resource files...\n");
	Log::getInstance().indent();

	// Create and write the resource file contents
	LECF lecf(this);
	string resourceFileName = outputDirPath + _name + RESOURCE_FILE_EXTENSION;
	fstream resourceFile(resourceFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
	IO::setKey(_key);
	lecf.write(resourceFile);
	resourceFile.close();

	// Create and write the index file contents
	RNAM rnam(this);
	MAXS maxs(this);
	DROO droo(this);
	DSCR dscr(lecf.getLFLF(0));
	DSOU dsou(this, &lecf);
	DCOS dcos(this, &lecf);
	DCHR dchr(lecf.getLFLF(0));
	DOBJ dobj(this);
	AARY aary(this);
	string indexFileName = outputDirPath + _name + INDEX_FILE_EXTENSION;
	fstream indexFile(indexFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
	IO::setKey(_key);
	rnam.write(indexFile);
	maxs.write(indexFile);
	droo.write(indexFile);
	dscr.write(indexFile);
	dsou.write(indexFile);
	dcos.write(indexFile);
	dchr.write(indexFile);
	dobj.write(indexFile);
	aary.write(indexFile);
	indexFile.close();

	// Create and write the voice file contents only if necessary
	if (!_voices.empty())
	{
		SOU2 sou(this);
		string voiceFileName = outputDirPath + VOICE_FILE_NAME;
		fstream voiceFile(voiceFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
		IO::setKey(0);
		sou.write(voiceFile);
		voiceFile.close();
	}

	Log::getInstance().unIndent();
}

void Game::build(string outputDirPath)
{
	// Prepare, parse, compile, and generate the game
	prepare();
	parse();
	compile();
	generate(outputDirPath);
}

Game::~Game()
{
	for (int i = 0; i < _arrays.size(); i++)
		delete _arrays[i];
	for (int i = 0; i < _rooms.size(); i++)
		delete _rooms[i];
	for (int i = 0; i < _objects.size(); i++)
		delete _objects[i];
	for (int i = 0; i < _midis.size(); i++)
		delete _midis[i];
	for (int i = 0; i < _scripts.size(); i++)
		delete _scripts[i];
	for (int i = 0; i < _costumes.size(); i++)
		delete _costumes[i];
	for (int i = 0; i < _charsets.size(); i++)
		delete _charsets[i];
	for (int i = 0; i < _voices.size(); i++)
		delete _voices[i];
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	for (int i = 0; i < _functions.size(); i++)
		delete _functions[i];
}
