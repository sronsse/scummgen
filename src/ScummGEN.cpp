#include "ScummGEN.hpp"
#include "util/IO.hpp"
#include "types/Game.hpp"
#include "blocks/index/RNAM.hpp"
#include "blocks/index/MAXS.hpp"
#include "blocks/index/DROO.hpp"
#include "blocks/index/DSCR.hpp"
#include "blocks/index/DSOU.hpp"
#include "blocks/index/DCOS.hpp"
#include "blocks/index/DCHR.hpp"
#include "blocks/index/DOBJ.hpp"
#include "blocks/index/AARY.hpp"
#include "blocks/resource/LECF.hpp"
#include "blocks/voice/SOU.hpp"

const string ScummGEN::INDEX_FILE_EXTENSION = ".000";
const string ScummGEN::RESOURCE_FILE_EXTENSION = ".001";
const string ScummGEN::VOICE_FILE_NAME = "MONSTER.SOU";
const uint8_t ScummGEN::MAJOR_VERSION = 0;
const uint8_t ScummGEN::MINOR_VERSION = 1;
const char ScummGEN::VERSION_TYPE = 'a';

ScummGEN::ScummGEN(Game *game, string outputDirName)
{
	_game = game;
	_outputDirName = outputDirName;

	writeResourceFile();
	writeIndexFile();
	writeVoiceFile();
}

void ScummGEN::writeIndexFile()
{
	// Create and write the index file contents
	_rnam = new RNAM(_game);
	_maxs = new MAXS(_game);
	_droo = new DROO(_game);
	_dscr = new DSCR(_game, _lecf->getLFLF(0));
	_dsou = new DSOU(_game, _lecf);
	_dcos = new DCOS(_game, _lecf);
	_dchr = new DCHR(_game, _lecf->getLFLF(0));
	_dobj = new DOBJ(_game);
	//_aary = new AARY(indexFile);
	string indexFileName = _outputDirName + _game->getShortName() + INDEX_FILE_EXTENSION;
	fstream indexFile(indexFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
	_rnam->write(indexFile);
	_maxs->write(indexFile);
	_droo->write(indexFile);
	_dscr->write(indexFile);
	_dsou->write(indexFile);
	_dcos->write(indexFile);
	_dchr->write(indexFile);
	_dobj->write(indexFile);
	//_aary->write(indexFile);

	// Encrypt the file
	uint32_t fileSize = indexFile.tellp();
	uint8_t byte;
	for (int i = 0; i < fileSize; i++)
	{
		indexFile.seekg(i, ios::beg);
		byte = IO::readU8(indexFile);
		indexFile.seekp(i, ios::beg);
		IO::writeU8(indexFile, byte ^ _game->getKey());
	}

	indexFile.close();
}

void ScummGEN::writeResourceFile()
{
	// Create and write the resource file contents
	_lecf = new LECF(_game);
	string resourceFileName = _outputDirName + _game->getShortName() + RESOURCE_FILE_EXTENSION;
	fstream resourceFile(resourceFileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
	_lecf->write(resourceFile);

	// Encrypt the file
	uint32_t fileSize = resourceFile.tellp();
	uint8_t byte;
	for (int i = 0; i < fileSize; i++)
	{
		resourceFile.seekg(i, ios::beg);
		byte = IO::readU8(resourceFile);
		resourceFile.seekp(i, ios::beg);
		IO::writeU8(resourceFile, byte ^ _game->getKey());
	}

	resourceFile.close();
}

void ScummGEN::writeVoiceFile()
{
	// Create and write the voice file contents only if necessary
	if (_game->getNumberOfVoices() > 0)
	{
		_sou = new SOU(_game);
		string voiceFileName = _outputDirName + VOICE_FILE_NAME;
		fstream voiceFile(voiceFileName.c_str(), ios::out | ios::binary | ios::trunc);
		_sou->write(voiceFile);
		voiceFile.close();
	}
}

ScummGEN::~ScummGEN()
{
	delete _rnam;
	delete _maxs;
	delete _droo;
	delete _dscr;
	delete _dsou;
	delete _dcos;
	delete _dchr;
	delete _dobj;
	//delete _aary;
	delete _lecf;
	if (_game->getNumberOfVoices() > 0)
		delete _sou;
}

