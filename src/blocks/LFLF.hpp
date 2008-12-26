#ifndef _LFLF_BLOCK_HPP_
#define _LFLF_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Game;
class ROOM;
class SCRP;
class SOUN;
class COST;
class CHAR;

class LFLF
{
private:
	uint32_t _size;
	ROOM *_room;
	vector<SCRP *> _scrps;
	vector<SOUN *> _souns;
	vector<COST *> _costs;
	vector<CHAR *> _chars;
	vector<uint32_t> _scrpOffsets;
	vector<uint32_t> _sounOffsets;
	vector<uint32_t> _costOffsets;
	vector<uint32_t> _charOffsets;
public:
	LFLF(Game *game, uint8_t roomIndex);
	uint32_t getSize();
	uint32_t getNumberOfSCRPOffsets() { return _scrpOffsets.size(); }
	uint32_t getSCRPOffset(uint32_t index) { return _scrpOffsets[index]; }
	uint32_t getNumberOfSOUNOffsets() { return _sounOffsets.size(); }
	uint32_t getSOUNOffset(uint32_t index) { return _sounOffsets[index]; }
	uint32_t getNumberOfCOSTOffsets() { return _costOffsets.size(); }
	uint32_t getCOSTOffset(uint32_t index) { return _costOffsets[index]; }
	uint32_t getNumberOfCHAROffsets() { return _charOffsets.size(); }
	uint32_t getCHAROffset(uint32_t index) { return _charOffsets[index]; }
	void write(fstream &f);
	~LFLF();
};

#endif

