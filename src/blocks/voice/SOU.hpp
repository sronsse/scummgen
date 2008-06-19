#ifndef _SOU_BLOCK_HPP_
#define _SOU_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class VCTL;
class VOC;

class SOU
{
private:
	uint16_t _nVoices;
	vector<VCTL *> _vctls;
	vector<VOC *> _vocs;
public:
	SOU(Game *game);
	uint32_t getSize();
	void write(fstream &f);
	~SOU();
};

#endif

