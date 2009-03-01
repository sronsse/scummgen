#include "ScummGEN.hpp"
#include "util/IO.hpp"
#include "util/Log.hpp"
#include "types/Game.hpp"
#include "grammar/Expression.hpp"
#include "grammar/Instruction.hpp"
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

const string ScummGEN::INDEX_FILE_EXTENSION = ".000";
const string ScummGEN::RESOURCE_FILE_EXTENSION = ".001";
const string ScummGEN::VOICE_FILE_NAME = "MONSTER.SOU";

ScummGEN &ScummGEN::getInstance()
{
	static ScummGEN instance;
	return instance;
}

ScummGEN::ScummGEN()
{
	_game = NULL;

	// Set up opcodes table
	Instruction::setOpcodes();
}

void ScummGEN::writeIndexFile(string outputDirName)
{
	// Create and write the index file contents
	RNAM rnam(_game);
	MAXS maxs(_game);
	DROO droo(_game);
	DSCR dscr(_lecf->getLFLF(0));
	DSOU dsou(_game, _lecf);
	DCOS dcos(_game, _lecf);
	DCHR dchr(_lecf->getLFLF(0));
	DOBJ dobj(_game);
	AARY aary(_game);
	string indexFileName = outputDirName + _game->getShortName() + INDEX_FILE_EXTENSION;
	fstream indexFile(indexFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
	IO::setKey(_game->getKey());
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
}

void ScummGEN::writeResourceFile(string outputDirName)
{
	// Create and write the resource file contents
	_lecf = new LECF(_game);
	string resourceFileName = outputDirName + _game->getShortName() + RESOURCE_FILE_EXTENSION;
	fstream resourceFile(resourceFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
	IO::setKey(_game->getKey());
	_lecf->write(resourceFile);
	resourceFile.close();
}

void ScummGEN::writeVoiceFile(string outputDirName)
{
	// Create and write the voice file contents only if necessary
	if (_game->getNumberOfVoices() > 0)
	{
		SOU2 sou(_game);
		string voiceFileName = outputDirName + VOICE_FILE_NAME;
		fstream voiceFile(voiceFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
		IO::setKey(0);
		sou.write(voiceFile);
		voiceFile.close();
	}
}

void ScummGEN::load(string dirName)
{
	Log::getInstance().write(LOG_INFO, "Loading game data structures...\n");
	Log::getInstance().indent();

	_game = new Game();
	_game->load(dirName);
	_game->parse();
	_game->compile();

	Log::getInstance().unIndent();
}

void ScummGEN::generate(string outputDirName)
{
	Log::getInstance().write(LOG_INFO, "Generating game resource files...\n");
	Log::getInstance().indent();

	writeResourceFile(outputDirName);
	writeIndexFile(outputDirName);
	writeVoiceFile(outputDirName);

	Log::getInstance().unIndent();
}

ScummGEN::~ScummGEN()
{
	if (_game != NULL);
		delete _game;
	if (_lecf != NULL)
		delete _lecf;
}

