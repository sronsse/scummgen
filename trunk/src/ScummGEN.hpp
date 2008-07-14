#ifndef _SCUMMGEN_HPP_
#define _SCUMMGEN_HPP_

#include <string>
using namespace std;

class Game;
class RNAM;
class MAXS;
class DROO;
class DSCR;
class DSOU;
class DCOS;
class DCHR;
class DOBJ;
class AARY;
class LECF;
class SOU;

class ScummGEN
{
private:
	static const string INDEX_FILE_EXTENSION;
	static const string RESOURCE_FILE_EXTENSION;
	static const string VOICE_FILE_NAME;

	Game *_game;
	string _outputDirName;
	RNAM *_rnam;
	MAXS *_maxs;
	DROO *_droo;
	DSCR *_dscr;
	DSOU *_dsou;
	DCOS *_dcos;
	DCHR *_dchr;
	DOBJ *_dobj;
	AARY *_aary;
	LECF *_lecf;
	SOU *_sou;

	void writeIndexFile();
	void writeResourceFile();
	void writeVoiceFile();
public:
	static const uint8_t MAJOR_VERSION;
	static const uint8_t MINOR_VERSION;
	static const char VERSION_TYPE;

	ScummGEN(Game *game, string outputDirName);
	~ScummGEN();
};

#endif

