#ifndef _SOU2_BLOCK_HPP_
#define _SOU2_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;
class VCTL;
class VOC;

class SOU2
{
private:
	uint16_t _nVoices;
	vector<VCTL *> _vctls;
	vector<VOC *> _vocs;
public:
	SOU2(Game *game);
	uint32_t getSize();
	void write(fstream &f);
	~SOU2();
};

#endif

