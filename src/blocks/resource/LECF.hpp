#ifndef _LECF_BLOCK_HPP_
#define _LECF_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class LOFF;
class LFLF;

class LECF
{
private:
	LOFF *_loff;
	vector<LFLF *> _lflfs;

	uint32_t getSize();
public:
	LECF(Game *game);
	LFLF *getLFLF(uint8_t index) { return _lflfs[index]; }
	void write(ofstream &f);
	~LECF();
};

#endif

