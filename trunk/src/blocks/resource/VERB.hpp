#ifndef _VERB_BLOCK_HPP_
#define _VERB_BLOCK_HPP_

#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

class Script;

class VERB
{
private:
	vector<uint8_t> _bytes;
public:
	VERB(Script *script);
	uint32_t getSize();
	void write(fstream &f);
	~VERB();
};

#endif

