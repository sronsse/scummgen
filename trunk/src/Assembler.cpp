#include "Assembler.hpp"
#include "types/Game.hpp"
#include "blocks/index/RNAM.hpp"
#include "blocks/index/MAXS.hpp"
#include "blocks/index/DROO.hpp"
#include "blocks/index/DRSC.hpp"
#include "blocks/index/DSCR.hpp"
#include "blocks/index/DSOU.hpp"
#include "blocks/index/DCOS.hpp"
#include "blocks/index/DCHR.hpp"
#include "blocks/index/DOBJ.hpp"
#include "blocks/index/AARY.hpp"
#include "blocks/resource/LECF.hpp"

const string Assembler::INDEX_FILE_EXTENSION = ".la0";
const string Assembler::RESOURCE_FILE_EXTENSION = ".la1";
const uint8_t Assembler::MAJOR_VERSION = 0;
const uint8_t Assembler::MINOR_VERSION = 1;
const char Assembler::VERSION_TYPE = 'a';

Assembler::Assembler(Game *game, string outputDirName):
_game(game),
_outputDirName(outputDirName)
{
	writeResourceFile();
	writeIndexFile();
}

void Assembler::writeIndexFile()
{
	_rnam = new RNAM(_game);
	_maxs = new MAXS(_game);
	_droo = new DROO(_game);
	_drsc = new DRSC(_game, _lecf);
	_dscr = new DSCR(_game, _lecf);
	/*_dsou = new DSOU(indexFile);
	_dcos = new DCOS(indexFile);
	_dchr = new DCHR(indexFile);*/
	_dobj = new DOBJ(_game);
	//_aary = new AARY(indexFile);
	string indexFileName = _outputDirName + _game->getShortName() + INDEX_FILE_EXTENSION;
	ofstream indexFile(indexFileName.c_str(), ios::out | ios::binary);
	_rnam->write(indexFile);
	_maxs->write(indexFile);
	_droo->write(indexFile);
	_drsc->write(indexFile);
	_dscr->write(indexFile);
	/*_dsou->write(indexFile);
	_dcos->write(indexFile);
	_dchr->write(indexFile);*/
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

Assembler::~Assembler()
{
	delete _rnam;
	delete _maxs;
	delete _droo;
	delete _drsc;
	delete _dscr;
	/*delete _dsou;
	delete _dcos;
	delete _dchr;*/
	delete _dobj;
	//delete _aary;
	delete _lecf;
}

