#ifndef _PALETTE_HPP_
#define _PALETTE_HPP_

#include <stdint.h>
#include <vector>
#include <string>
#include "util/BMPFile.hpp"
using namespace std;

class XMLNode;

class Area
{
private:
	string _name;
	uint8_t _start;
	uint8_t _end;
public:
	Area();
	void load(XMLNode *node);
	void save(XMLNode *node);
	string getName() { return _name; }
	void setName(string name) { _name = name; }
	uint8_t getStart()  { return _start; }
	void setStart(uint8_t start) { _start = start; }
	uint8_t getEnd() { return _end; }
	void setEnd(uint8_t end) { _end = end; }
	~Area();
};

class Cycle
{
private:
	uint8_t _id;
	string _name;
	uint8_t _start;
	uint8_t _end;
	uint8_t _delay;
	bool _forward;
public:
	Cycle();
	void load(XMLNode *node);
	void save(XMLNode *node);
	uint8_t getID() { return _id; }
	void setID(uint8_t id) { _id = id; }
	string getName() { return _name; }
	void setName(string name) { _name = name; }
	uint8_t getStart()  { return _start; }
	void setStart(uint8_t start) { _start = start; }
	uint8_t getEnd() { return _end; }
	void setEnd(uint8_t end) { _end = end; }
	uint8_t getDelay()  { return _delay; }
	void setDelay(uint8_t delay)  { _delay = delay; }
	bool isForward() { return _forward; }
	void setForward(bool forward)  { _forward = forward; }
	~Cycle();
};

class PaletteData
{
private:
	static const string XML_FILE_NAME;

	bool _transparent;
	vector<Area *> _areas;
	vector<Cycle *> _cycles;
public:
	PaletteData();
	void load(string dirName);
	void save(string dirName);
	bool isTransparent() { return _transparent; }
	uint8_t getNumberOfAreas() { return _areas.size(); }
	Area *getArea(uint8_t index) { return _areas[index]; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint8_t index) { return _cycles[index]; }
	~PaletteData();
};

class Palette
{
private:
	static const string XML_FILE_NAME;
	static const uint8_t MAX_CYCLES;
	static const uint8_t N_EGA_COLORS;
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

	bool _local;
	vector<Color> _colors;
	vector<Area *> _areas;
	vector<Cycle *> _cycles;
	uint16_t _cursor;
	vector<bool> _reserved;

	uint8_t addColor(Color *c, bool reserved);
	int16_t findColor(Color *c);
public:
	static const uint16_t MAX_COLORS;

	Palette(bool local);
	void prepare();
	void add(vector<Color> *colors, vector<vector<uint8_t> > &pixels, PaletteData *paletteData);
	Color getColor(uint8_t index) { return _colors[index]; }
	uint8_t getNumberOfAreas() { return _areas.size(); }
	Area *getArea(uint8_t index) { return _areas[index]; }
	uint8_t getNumberOfCycles() { return _cycles.size(); }
	Cycle *getCycle(uint8_t index) { return _cycles[index]; }
	uint16_t getCursor() { return _cursor; }
	~Palette();
};

#endif
