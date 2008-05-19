#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class Script
{
	uint32_t _id;
public:
	Script(string fileName);
	uint32_t getID() { return _id; }
	uint32_t getNumberOfBytes() { return 0; }
	uint32_t getByte(uint32_t index) { return 0; }
	~Script();
};

#endif

