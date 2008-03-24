#ifndef _MAXS_BLOCK_HPP_
#define _MAXS_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
using namespace std;

class Game;

class MAXS
{
private:
	static const uint8_t N_CHARS;
	static const uint8_t UNKNOWN1;
	static const uint8_t UNKNOWN2;
	static const uint8_t UNKNOWN3;

	string _engineVersion;
	string _dataFileVersion;
	uint32_t _nVariables;
	uint32_t _nBitVariables;
	uint32_t _nScripts;
	uint32_t _nSounds;
	uint32_t _nCharsets;
	uint32_t _nCostumes;
	uint32_t _nRooms;
	uint32_t _nGlobalObjects;
	uint32_t _nLocalObjects;
	uint32_t _nNewNames;
	uint32_t _nFlObjects;
	uint32_t _nInventories;
	uint32_t _nArrays;
	uint32_t _nVerbs;

	uint32_t getSize();
public:
	MAXS(Game *game);
	void write(ofstream &f);
	~MAXS();
};

#endif

