#ifndef _PALETTE_HPP_
#define _PALETTE_HPP_

#include <stdint.h>
#include <vector>
#include <string>
#include "util/BMPFile.hpp"
using namespace std;

class XMLNode;

class Cycle
{
private:
	uint8_t _id;
	uint8_t _start;
	uint8_t _end;
	uint8_t _delay;
	bool _forward;
public:
	Cycle(XMLNode *node);
	uint8_t getID()  { return _id; }
	uint8_t getStart()  { return _start; }
	uint8_t getEnd() { return _end; }
	uint8_t getDelay()  { return _delay; }
	bool isForward() { return _forward; }
	~Cycle();
};

class Palette
{
private:
	vector<Color> _colors;
	vector<Cycle *> _cycles;
	uint8_t _transparentIndex;
public:
	Palette(string dirName);
	uint32_t getNumberOfColors() { return _colors.size(); }
	Color getColor(uint32_t index) { return _colors[index]; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint32_t index) { return _cycles.at(index); }
	uint8_t getTransparentIndex() { return _transparentIndex; }
	~Palette();
};

#endif

