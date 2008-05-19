#include "Assembler.hpp"
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

const string Assembler::INDEX_FILE_EXTENSION = ".000";
const string Assembler::RESOURCE_FILE_EXTENSION = ".001";
const string Assembler::VOICE_FILE_NAME = "MONSTER.SOU";
const uint8_t Assembler::MAJOR_VERSION = 0;
const uint8_t Assembler::MINOR_VERSION = 1;
const char Assembler::VERSION_TYPE = 'a';

Assembler::Assembler(Game *game, string outputDirName):
_game(game),
_outputDirName(outputDirName)
{
	writeResourceFile();
	writeIndexFile();
	writeVoiceFile();
}

void Assembler::writeIndexFile()
{
	_rnam = new RNAM(_game);
	_maxs = new MAXS(_game);
	_droo = new DROO(_game);
	_dscr = new DSCR(_game, _lecf);
	//_dsou = new DSOU(_game, _lecf);
	_dcos = new DCOS(_game, _lecf);
	_dchr = new DCHR(_game, _lecf);
	_dobj = new DOBJ(_game);
	//_aary = new AARY(indexFile);
	string indexFileName = _outputDirName + _game->getShortName() + INDEX_FILE_EXTENSION;
	ofstream indexFile(indexFileName.c_str(), ios::out | ios::binary);
	_rnam->write(indexFile);
	_maxs->write(indexFile);
	_droo->write(indexFile);
	_dscr->write(indexFile);
	//_dsou->write(indexFile);
	_dcos->write(indexFile);
	_dchr->write(indexFile);
	_dobj->write(indexFile);
	//_aary->write(indexFile);
	indexFile.close();
}

void Assembler::writeResourceFile()
{
	_lecf = new LECF(_game);
	string resourceFileName = _outputDirName + _game->getShortName() + RESOURCE_FILE_EXTENSION;
	ofstream resourceFile(resourceFileName.c_str(), ios::out | ios::binary);
	_lecf->write(resourceFile);
	resourceFile.close();
}

void Assembler::writeVoiceFile()
{
	_sou = new SOU(_game);
	string voiceFileName = _outputDirName + VOICE_FILE_NAME;
	ofstream voiceFile(voiceFileName.c_str(), ios::out | ios::binary);
	_sou->write(voiceFile);
	voiceFile.close();
}

Assembler::~Assembler()
{
	delete _rnam;
	delete _maxs;
	delete _droo;
	delete _dscr;
	//delete _dsou;
	delete _dcos;
	delete _dchr;
	delete _dobj;
	//delete _aary;
	delete _lecf;
	delete _sou;
}

