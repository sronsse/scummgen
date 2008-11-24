#ifndef _AARY_BLOCK_HPP_
#define _AARY_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Game;

class AARY
{
private:
	vector<uint16_t> _varNumbers;
	vector<uint16_t> _dimAs;
	vector<uint16_t> _dimBs;
	vector<uint16_t> _types;
public:
	AARY(Game *game);
	uint32_t getSize();
	void write(fstream &f);
	~AARY();
};

#endif
