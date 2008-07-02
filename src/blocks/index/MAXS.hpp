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
	static const uint16_t N_VARIABLES;
	static const uint8_t UNKNOWN1;
	static const uint16_t N_BIT_VARIABLES;
	static const uint8_t N_LOCAL_OBJECTS;
	static const uint8_t N_ARRAYS;
	static const uint8_t UNKNOWN2;
	static const uint8_t N_VERBS;
	static const uint8_t N_FL_OBJECTS;
	static const uint8_t N_INVENTORIES;

	uint16_t _nVariables;
	uint16_t _nBitVariables;
	uint16_t _nLocalObjects;
	uint16_t _nArrays;
	uint16_t _nVerbs;
	uint16_t _nFlObjects;
	uint16_t _nInventories;
	uint16_t _nRooms;
	uint16_t _nScripts;
	uint16_t _nSounds;
	uint16_t _nCharsets;
	uint16_t _nCostumes;
	uint16_t _nGlobalObjects;

	uint32_t getSize();
public:
	MAXS(Game *game);
	void write(fstream &f);
	~MAXS();
};

#endif

