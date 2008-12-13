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
	string _name;
	uint8_t _id;
	uint8_t _start;
	uint8_t _end;
	uint8_t _delay;
	bool _forward;
public:
	Cycle(XMLNode *node);
	string getName() { return _name; }
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
	static const uint16_t MAX_COLORS;

	Palette(string dirName);
	uint16_t getNumberOfColors() { return _colors.size(); }
	Color getColor(uint8_t index) { return _colors[index]; }
	void setColor(uint8_t index, Color color) { _colors[index] = color; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint8_t index) { return _cycles[index]; }
	uint8_t getTransparentIndex() { return _transparentIndex; }
	void resize(uint16_t size) { Color black = { 0, 0, 0 }; _colors.resize(size, black); }
	~Palette();
};

#endif

