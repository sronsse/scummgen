#ifndef _SCUMMGEN_HPP_
#define _SCUMMGEN_HPP_

#include <string>
using namespace std;

class Game;
class LECF;

class ScummGEN
{
private:
	static const string INDEX_FILE_EXTENSION;
	static const string RESOURCE_FILE_EXTENSION;
	static const string VOICE_FILE_NAME;

	Game *_game;
	LECF *_lecf;

	ScummGEN();
	void writeIndexFile(string outputDirName);
	void writeResourceFile(string outputDirName);
	void writeVoiceFile(string outputDirName);
	~ScummGEN();
public:
	static const uint8_t MAJOR_VERSION;
	static const uint8_t MINOR_VERSION;
	static const char VERSION_TYPE;

	static ScummGEN &getInstance();

	void load(string gameDir);
	void generate(string outputDir);
};

#endif

