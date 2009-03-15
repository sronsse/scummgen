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
	Cycle();
	void load(XMLNode *node);
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
	static const Color COLOR_BLACK;
	static const Color COLOR_DARK_BLUE;
	static const Color COLOR_JAPANESE_LAUREL;
	static const Color COLOR_PERSIAN_GREEN;
	static const Color COLOR_BRIGHT_RED;
	static const Color COLOR_FLIRT;
	static const Color COLOR_CHELSEA_GEM;
	static const Color COLOR_SILVER_CHALICE;
	static const Color COLOR_SCORPION;
	static const Color COLOR_DODGER_BLUE;
	static const Color COLOR_SCREAMIN_GREEN;
	static const Color COLOR_AQUAMARINE;
	static const Color COLOR_PERSIMMON;
	static const Color COLOR_PINK_FLAMINGO;
	static const Color COLOR_GORSE;
	static const Color COLOR_WHITE;

	vector<Color> _colors;
	vector<Cycle *> _cycles;
	uint8_t _transparentIndex;
	uint16_t _startCursor;
	uint16_t _endCursor;
public:
	static const uint16_t MAX_COLORS;

	Palette();
	void load(string dirName);
	Color getColor(uint8_t index) { return _colors[index]; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint8_t index) { return _cycles[index]; }
	uint8_t getTransparentIndex() { return _transparentIndex; }
	uint8_t add(string bitmapPath, bool fromStart);
	~Palette();
};

#endif
