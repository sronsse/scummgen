#ifndef _VERB_BLOCK_HPP_
#define _VERB_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Function;

class VERB
{
private:
	vector<uint8_t> _bytes;
public:
	VERB(Function *function);
	uint32_t getSize();
	void write(fstream &f);
	~VERB();
};

#endif

