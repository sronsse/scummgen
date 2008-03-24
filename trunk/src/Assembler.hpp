#ifndef _ASSEMBLER_HPP_
#define _ASSEMBLER_HPP_

#include <string>
using namespace std;

class Game;
class RNAM;
class MAXS;
class DROO;
class DRSC;
class DSCR;
class DSOU;
class DCOS;
class DCHR;
class DOBJ;
class AARY;
class LECF;

class Assembler
{
private:
	static const string INDEX_FILE_EXTENSION;
	static const string RESOURCE_FILE_EXTENSION;

	Game *_game;
	string _outputDirName;
	RNAM *_rnam;
	MAXS *_maxs;
	DROO *_droo;
	DRSC *_drsc;
	DSCR *_dscr;
	DSOU *_dsou;
	DCOS *_dcos;
	DCHR *_dchr;
	DOBJ *_dobj;
	AARY *_aary;
	LECF *_lecf;

	void writeIndexFile();
	void writeResourceFile();
public:
	static const uint8_t MAJOR_VERSION;
	static const uint8_t MINOR_VERSION;
	static const char VERSION_TYPE;

	Assembler(Game *game, string outputDirName);
	~Assembler();
};

#endif

