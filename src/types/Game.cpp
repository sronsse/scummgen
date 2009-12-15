#include "Game.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "util/WAVFile.hpp"
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

const string Game::XML_FILE_NAME = "game.xml";
const char *Game::INDEX_FILE_EXTENSION = ".000";
const char *Game::RESOURCE_FILE_EXTENSION = ".001";
const char *Game::VOICE_FILE_NAME = "MONSTER.SOU";
const string Game::LIB_SCUMM_DIR_PATH = "libscumm/";
const string Game::ACTOR_SCRIPT_NAME = "Actor.sgc";
const string Game::INTERFACE_SCRIPT_NAME = "Interface.sgc";
const string Game::OBJECT_SCRIPT_NAME = "Object.sgc";
const string Game::ROOM_SCRIPT_NAME = "Room.sgc";
const string Game::SCRIPT_SCRIPT_NAME = "Script.sgc";
const string Game::SOUND_SCRIPT_NAME = "Sound.sgc";
const string Game::UTIL_SCRIPT_NAME = "Util.sgc";
const string Game::VARS_SCRIPT_NAME = "vars.sgc";
const string Game::VERB_SCRIPT_NAME = "Verb.sgc";

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
	Log::write(LOG_INFO, "Array\n");
	Log::indent();

	_varNumber = node->getChild("varNumber")->getIntegerContent();
	Log::write(LOG_INFO, "varNumber: %u\n", _varNumber);

	_dimA = node->getChild("dimA")->getIntegerContent();
	Log::write(LOG_INFO, "dimA: %u\n", _dimA);

	_dimB = node->getChild("dimB")->getIntegerContent();
	Log::write(LOG_INFO, "dimB: %u\n", _dimB);

	_type = node->getChild("type")->getIntegerContent();
	Log::write(LOG_INFO, "type: %u\n", _type);

	Log::unIndent();
}

void Array::save(XMLNode *node)
{
	Log::write(LOG_INFO, "Array\n");
	Log::indent();

	node->addChild(new XMLNode("varNumber", _varNumber));
	Log::write(LOG_INFO, "varNumber: %u\n", _varNumber);

	node->addChild(new XMLNode("dimA", _dimA));
	Log::write(LOG_INFO, "dimA: %u\n", _dimA);

	node->addChild(new XMLNode("dimB", _dimB));
	Log::write(LOG_INFO, "dimB: %u\n", _dimB);

	node->addChild(new XMLNode("type", _type));
	Log::write(LOG_INFO, "type: %u\n", _type);

	Log::unIndent();
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

void Game::loadRooms(string dirPath, XMLNode *node)
{
	dirPath += "rooms/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("room", i++)) != NULL)
	{
		Room *room = new Room();
		room->load(dirPath + child->getStringContent() + '/');
		_rooms.push_back(room);
	}
}

void Game::loadObjects(string dirPath, XMLNode *node)
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

void Game::loadMidis(string dirPath, XMLNode *node)
{
	dirPath += "midis/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("midi", i++)) != NULL)
	{
		Midi *midi = new Midi();
		midi->load(dirPath + child->getStringContent() + '/');
		_midis.push_back(midi);
	}
}

void Game::loadCostumes(string dirPath, XMLNode *node)
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

void Game::loadScripts(string dirPath, XMLNode *node)
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

void Game::loadCharsets(string dirPath, XMLNode *node)
{
	dirPath += "charsets/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("charset", i++)) != NULL)
	{
		Charset *charset = new Charset();
		charset->load(dirPath + child->getStringContent() + '/');
		_charsets.push_back(charset);
	}
}

void Game::loadVoices(string dirPath, XMLNode *node)
{
	dirPath += "voices/";

	int i = 0;
	XMLNode *child;
	while ((child = node->getChild("voice", i++)) != NULL)
	{
		Voice *voice = new Voice();
		voice->load(dirPath + child->getStringContent() + '/');
		_voices.push_back(voice);
	}
}

void Game::saveRooms(string dirPath, XMLNode *node)
{
	if (_rooms.empty())
		return;

	dirPath += "rooms/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i]->save(dirPath + _rooms[i]->getName() + '/');
		node->addChild(new XMLNode("room", _rooms[i]->getName()));
	}
}

void Game::saveObjects(string dirPath, XMLNode *node)
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

void Game::saveMidis(string dirPath, XMLNode *node)
{
	if (_midis.empty())
		return;

	dirPath += "midis/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _midis.size(); i++)
	{
		_midis[i]->save(dirPath + _midis[i]->getName() + '/');
		node->addChild(new XMLNode("midi", _midis[i]->getName()));
	}
}

void Game::saveCostumes(string dirPath, XMLNode *node)
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

void Game::saveScripts(string dirPath, XMLNode *node)
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

void Game::saveCharsets(string dirPath, XMLNode *node)
{
	if (_charsets.empty())
		return;

	dirPath += "charsets/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _charsets.size(); i++)
	{
		_charsets[i]->save(dirPath + _charsets[i]->getName() + '/');
		node->addChild(new XMLNode("charset", _charsets[i]->getName()));
	}
}

void Game::saveVoices(string dirPath, XMLNode *node)
{
	if (_voices.empty())
		return;

	dirPath += "voices/";
	if (!IO::createDirectory(dirPath))
		Log::write(LOG_ERROR, "Could not create directory \"%s\" !\n", dirPath.c_str());

	for (int i = 0; i < _voices.size(); i++)
	{
		_voices[i]->save(dirPath + _voices[i]->getName() + '/');
		node->addChild(new XMLNode("voice", _voices[i]->getName()));
	}
}

void Game::load(string dirPath)
{
	Log::write(LOG_INFO, "Game\n");
	Log::indent();

	XMLFile xmlFile;
	if (!xmlFile.open(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't find any game in the specified directory !\n");
	XMLNode *rootNode = xmlFile.getRootNode();

	_name = rootNode->getChild("name")->getStringContent();
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	_description = rootNode->getChild("description")->getStringContent();
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	_key = rootNode->getChild("key")->getIntegerContent();
	Log::write(LOG_INFO, "key: 0x%02x\n", _key);

	int i = 0;
	XMLNode *child;
	while ((child = rootNode->getChild("array", i++)) != NULL)
	{
		Array *array = new Array();
		array->load(child);
		_arrays.push_back(array);
	}

	_palette = new Palette(false);

	loadRooms(dirPath, rootNode);
	loadObjects(dirPath, rootNode);
	loadMidis(dirPath, rootNode);
	loadCostumes(dirPath, rootNode);
	loadScripts(dirPath, rootNode);
	loadCharsets(dirPath, rootNode);
	loadVoices(dirPath, rootNode);

	Log::unIndent();
}

void Game::save(string dirPath)
{
	Log::write(LOG_INFO, "Game\n");
	Log::indent();

	XMLFile xmlFile;
	XMLNode *rootNode = new XMLNode("game");
	xmlFile.setRootNode(rootNode);

	rootNode->addChild(new XMLNode("name", _name));
	Log::write(LOG_INFO, "name: %s\n", _name.c_str());

	rootNode->addChild(new XMLNode("description", _description));
	Log::write(LOG_INFO, "description: %s\n", _description.c_str());

	rootNode->addChild(new XMLNode("key", _key));
	Log::write(LOG_INFO, "key: 0x%02x\n", _key);

	for (int i = 0; i < _arrays.size(); i++)
	{
		XMLNode *child = new XMLNode("array");
		rootNode->addChild(child);
		_arrays[i]->save(child);
	}

	saveRooms(dirPath, rootNode);
	saveObjects(dirPath, rootNode);
	saveMidis(dirPath, rootNode);
	saveCostumes(dirPath, rootNode);
	saveScripts(dirPath, rootNode);
	saveCharsets(dirPath, rootNode);
	saveVoices(dirPath, rootNode);

	if (!xmlFile.save(dirPath + XML_FILE_NAME))
		Log::write(LOG_ERROR, "Couldn't save game to the specified directory !\n");

	Log::unIndent();
}

void Game::prepare()
{
	Log::write(LOG_INFO, "Preparing game...\n");
	Log::indent();

	// Check for compulsory resources
	if (_rooms.empty())
		Log::write(LOG_ERROR, "Game doesn't contain any room !\n");
	if (_charsets.empty())
		Log::write(LOG_ERROR, "Game doesn't contain any charset !\n");

	// Prepare palette
	_palette->prepare();

	// Prepare objects
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->prepare(_palette);

	// Prepare costumes
	for (int i = 0; i < _costumes.size(); i++)
		_costumes[i]->prepare(_palette);

	// Prepare rooms
	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i]->prepare();
		if (_palette->getCursor() <= _rooms[i]->getPalette()->getCursor())
			Log::write(LOG_ERROR, "Palette in room \"%s\" contains too many colors !\n", _rooms[i]->getName().c_str());
	}

	// Set resource IDs
	uint8_t roomID = 1;
	uint16_t objectID = N_DEFAULT_ACTORS + 1;
	uint16_t midiID = 1;
	uint16_t costumeID = 1;
	uint16_t charsetID = 1;
	uint16_t cycleID = 1;
	for (int i = 0; i < _objects.size(); i++)
		_objects[i]->setID(objectID++);
	for (int i = 0; i < _midis.size(); i++)
		_midis[i]->setID(midiID++);
	for (int i = 0; i < _costumes.size(); i++)
		_costumes[i]->setID(costumeID++);
	for (int i = 0; i < _charsets.size(); i++)
		_charsets[i]->setID(charsetID++);
	for (int i = 0; i < _palette->getNumberOfCycles(); i++)
		_palette->getCycle(i)->setID(cycleID++);
	if (!_voices.empty())
	{
		uint32_t voiceID =	0;
		voiceID += 4 * sizeof(uint8_t); // SOU2 identifier
		voiceID += sizeof(uint32_t); // SOU2 empty field
		_voices[0]->setID(voiceID);
		for (int i = 1; i < _voices.size(); i++)
		{
			voiceID += 4 * sizeof(uint8_t); // VCTL identifier
			voiceID += sizeof(uint32_t); // VCTL size
			voiceID += _voices[i - 1]->getNumberOfSyncTimes() * sizeof(uint16_t); // VCTL syncTimes
			voiceID += 19 * sizeof(uint8_t); // VOC identifier
			voiceID += sizeof(uint8_t); // VOC EOF
			voiceID += sizeof(uint16_t); // VOC HEADER_SIZE
			voiceID += sizeof(uint16_t); // VOC FILE_VERSION
			voiceID += sizeof(uint16_t); // VOC ~VERSION + MAGIC_NUMBER
			voiceID += sizeof(uint8_t); // VOC SOUND_DATA_BLOCK_ID
			voiceID += 3 * sizeof(uint8_t); // VOC 2 + _nDataBytes
			voiceID += sizeof(uint8_t); // VOC freqDivisor
			voiceID += sizeof(uint8_t); // VOC PCM_CODEC_ID
			WAVFile wavFile;
			wavFile.open(_voices[i - 1]->getWavePath());
			voiceID += wavFile.getNumberOfDataBytes() * sizeof(uint8_t); // VOC dataBytes
			voiceID += sizeof(uint8_t); // VOC TERMINATOR_BLOCK_ID
			_voices[i]->setID(voiceID);
		}
	}
	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i]->setID(roomID++);
		for (int j = 0; j < _rooms[i]->getNumberOfObjects(); j++)
			_rooms[i]->getObject(j)->setID(objectID++);
		for (int j = 0; j < _rooms[i]->getNumberOfCostumes(); j++)
			_rooms[i]->getCostume(j)->setID(costumeID++);
		for (int j = 0; j < _rooms[i]->getPalette()->getNumberOfCycles(); j++)
			_rooms[i]->getPalette()->getCycle(j)->setID(cycleID + j);
	}

	// Clear declarations and functions
	for (int i = 0; i < _declarations.size(); i++)
		delete _declarations[i];
	_declarations.clear();
	for (int i = 0; i < _functions.size(); i++)
		delete _functions[i];
	_functions.clear();

	Log::unIndent();
}

void Game::parse(string programDirPath)
{
	Log::write(LOG_INFO, "Parsing game...\n");
	Log::indent();

	// Parse libscumm first
	parseLibScumm(programDirPath);

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
					Log::write(LOG_ERROR, "Function \"main\" can't be inlined !\n");
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
							Log::write(LOG_ERROR, "Function \"%s\" can't be inlined !\n", functions[j]->getName().c_str());
						Log::write(LOG_INFO, "Attaching \"verb\" to object \"%s\"...\n", _objects[k]->getName().c_str());
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
		Log::write(LOG_ERROR, "Couldn't find the main function !\n");

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

	// Room declarations
	for (int i = 0; i < _rooms.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _rooms[i]->getName(), _rooms[i]->getID()));

	// Global objects declarations
	for (int i = 0; i < _objects.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _objects[i]->getName(), _objects[i]->getID()));
	
	// Local objects declarations (this is necessary for global inventory scripts which need local objects names)
	for (int i = 0; i < _rooms.size(); i++)
		for (int j = 0; j < _rooms[i]->getNumberOfObjects(); j++)
			_declarations.push_back(new Declaration(DECLARATION_CONST, _rooms[i]->getObject(j)->getName(), _rooms[i]->getObject(j)->getID()));

	// Midi declarations
	for (int i = 0; i < _midis.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _midis[i]->getName(), _midis[i]->getID()));
	
	// Costume declarations
	for (int i = 0; i < _costumes.size(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName(), _costumes[i]->getID()));
		for (int j = 0; j < _costumes[i]->getNumberOfAnims(); j++)
			_declarations.push_back(new Declaration(DECLARATION_CONST, _costumes[i]->getName() + "_" + _costumes[i]->getAnim(j)->getName(), _costumes[i]->getAnim(j)->getID()));
	}

	// Charset declarations
	for (int i = 0; i < _charsets.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _charsets[i]->getName(), _charsets[i]->getID()));

	// Voice declarations
	for (int i = 0; i < _voices.size(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _voices[i]->getName(), _voices[i]->getID()));

	// Areas declarations
	for (int i = 0; i < _palette->getNumberOfAreas(); i++)
	{
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getArea(i)->getName() + "_start", _palette->getArea(i)->getStart()));
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getArea(i)->getName() + "_end", _palette->getArea(i)->getEnd()));
	}

	// Cycles declarations
	for (int i = 0; i < _palette->getNumberOfCycles(); i++)
		_declarations.push_back(new Declaration(DECLARATION_CONST, _palette->getCycle(i)->getName(), _palette->getCycle(i)->getID()));

	// Parse rooms
	for (int i = 0; i < _rooms.size(); i++)
		_rooms[i]->parse(_declarations);

	Log::unIndent();
}

void Game::parseLibScumm(string programDirPath)
{
	// Create libscumm scripts first
	Script actorScript(programDirPath + LIB_SCUMM_DIR_PATH + ACTOR_SCRIPT_NAME);
	Script interfaceScript(programDirPath + LIB_SCUMM_DIR_PATH + INTERFACE_SCRIPT_NAME);
	Script objectScript(programDirPath + LIB_SCUMM_DIR_PATH + OBJECT_SCRIPT_NAME);
	Script roomScript(programDirPath + LIB_SCUMM_DIR_PATH + ROOM_SCRIPT_NAME);
	Script scriptScript(programDirPath + LIB_SCUMM_DIR_PATH + SCRIPT_SCRIPT_NAME);
	Script soundScript(programDirPath + LIB_SCUMM_DIR_PATH + SOUND_SCRIPT_NAME);
	Script utilScript(programDirPath + LIB_SCUMM_DIR_PATH + UTIL_SCRIPT_NAME);
	Script varsScript(programDirPath + LIB_SCUMM_DIR_PATH + VARS_SCRIPT_NAME);
	Script verbScript(programDirPath + LIB_SCUMM_DIR_PATH + VERB_SCRIPT_NAME);

	// Regroup scripts in a new list
	vector<Script *> libscumm;
	libscumm.push_back(&actorScript);
	libscumm.push_back(&interfaceScript);
	libscumm.push_back(&objectScript);
	libscumm.push_back(&roomScript);
	libscumm.push_back(&scriptScript);
	libscumm.push_back(&soundScript);
	libscumm.push_back(&utilScript);
	libscumm.push_back(&varsScript);
	libscumm.push_back(&verbScript);

	// Parse scripts
	for (int i = 0; i < libscumm.size(); i++)
	{
		vector<Function *> functions;
		libscumm[i]->parse(_declarations, functions);
		for (int j = 0; j < functions.size(); j++)
			_functions.push_back(functions[j]);
	}
}

void Game::compile()
{
	Log::write(LOG_INFO, "Compiling game...\n");
	Log::indent();

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

	Log::unIndent();
}

void Game::generate(string outputDirPath)
{
	Log::write(LOG_INFO, "Generating game resource files...\n");
	Log::indent();

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

	Log::unIndent();
}

void Game::build(string programDirPath, string outputDirPath)
{
	// Prepare, parse, compile, and generate the game
	prepare();
	parse(programDirPath);
	compile();
	generate(outputDirPath);
}

Game::~Game()
{
	if (_palette != NULL)
		delete _palette;
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
